#include "bsp_gpio.h"
#include "MKL25Z4.h"

GPIO_MemMapPtr GpioPortArray[BASE_NUM] =  { PTA_BASE_PTR, PTB_BASE_PTR, PTC_BASE_PTR, PTD_BASE_PTR, PTE_BASE_PTR };
PORT_MemMapPtr xxxPortArray[BASE_NUM] = {PORTA_BASE_PTR, PORTB_BASE_PTR, PORTC_BASE_PTR, PORTD_BASE_PTR, PORTE_BASE_PTR};

void enableClkToPorts(){    // must be called first
    SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
}

void setDirection(Port port, bit_t value){
    WRITE_BIT(GpioPortArray[port.base]->PDDR, port.bit, value);
}
bit_t getDirection(Port port){
    return GET_BIT_VALUE(GpioPortArray[port.base]->PDDR, port.bit);
}
//-----------
bit_t getInputData(Port port){
    //assert(getDirection(port) == INPUT);
    return GET_BIT_VALUE(GpioPortArray[port.base]->PDOR, port.bit);
}
//--------
void setOutputData(Port port, bit_t value){
    //assert(getDirection(port) == OUTPUT);
    WRITE_BIT(GpioPortArray[port.base]->PDOR, port.bit, value);
}
void togglePin(Port port){
    //assert(getDirection(port) == OUTPUT);
    GpioPortArray[port.base]->PTOR |= BIT(port.bit);
}

bit_t getOutputData(Port port){
    //assert(getDire    ction(port) == OUTPUT);
    return GET_BIT_VALUE(GpioPortArray[port.base]->PDOR, port.bit);
}
//--------
void clearIRQFlag(Port port){
    xxxPortArray[port.base]->ISFR |= BIT(port.bit);     // clear ISFR is done by writing 1
}
bit_t getIRQFlag(Port port){
    //assert(port.base == BASE_A || port.base == BASE_D);
    return GET_BIT_VALUE(xxxPortArray[port.base]->ISFR, port.bit);
}
//--------
void setPortRole(Port port, PortRole role){
	// Not all pins support all pin muxing slots (can cause exception)
    WRITE_MASK(xxxPortArray[port.base]->PCR[port.bit], PORT_PCR_MUX_MASK, PORT_PCR_MUX_SHIFT, role);
}
PortRole getPortRole(Port port){
    return (PortRole)GET_MASK_VALUE(xxxPortArray[port.base]->PCR[port.bit],PORT_PCR_MUX_MASK, PORT_PCR_MUX_SHIFT);
}
//--------
void setIRQType(Port port, IRQType irqType){
    WRITE_MASK(xxxPortArray[port.base]->PCR[port.bit], PORT_PCR_IRQC_MASK, PORT_PCR_IRQC_SHIFT, irqType);
}
IRQType getIRQType(Port port){
    return (IRQType)GET_MASK_VALUE(xxxPortArray[port.base]->PCR[port.bit],PORT_PCR_IRQC_MASK,  PORT_PCR_IRQC_SHIFT);
}
//--------
void setHighDriveStrength(Port port){
    xxxPortArray[port.base]->PCR[port.bit] |= PORT_PCR_DSE_MASK;
}
bit_t getDriveStrength(Port port){
    return (bit_t)GET_MASK_VALUE(xxxPortArray[port.base]->PCR[port.bit],PORT_PCR_DSE_MASK,  PORT_PCR_DSE_SHIFT);
}
//--------
void setSlowSlewRate(Port port){
    xxxPortArray[port.base]->PCR[port.bit] |= PORT_PCR_SRE_MASK;
}
bit_t getSlewRate(Port port){
    return (bit_t)GET_MASK_VALUE(xxxPortArray[port.base]->PCR[port.bit],PORT_PCR_SRE_MASK,  PORT_PCR_SRE_SHIFT);
}//--------
void setPullEnable(Port port){
    xxxPortArray[port.base]->PCR[port.bit] |= PORT_PCR_PE_MASK;
}
bit_t getPullEnable(Port port){
    return (bit_t)GET_MASK_VALUE(xxxPortArray[port.base]->PCR[port.bit],PORT_PCR_PE_MASK,  PORT_PCR_PE_SHIFT);
}//--------
void setPullSelect(Port port){
    xxxPortArray[port.base]->PCR[port.bit] |= PORT_PCR_PS_MASK;
}
bit_t getPullSelect(Port port){
    return (bit_t)GET_MASK_VALUE(xxxPortArray[port.base]->PCR[port.bit],PORT_PCR_PS_MASK,  PORT_PCR_PS_SHIFT);
}
//--------
void setPassiveFilter(Port port){
    xxxPortArray[port.base]->PCR[port.bit] |= PORT_PCR_PFE_MASK;
}
bit_t getPassiveFilter(Port port){
    return (bit_t)GET_MASK_VALUE(xxxPortArray[port.base]->PCR[port.bit],PORT_PCR_PFE_MASK,  PORT_PCR_PFE_SHIFT);
}
//--------

void InitInput(Port port){
    setDirection(port, INPUT);
    setPortRole(port, GPIO_ROLE);
    setPassiveFilter(port);
    setPullEnable(port);
    setPullSelect(port);
}
void initOutput(Port port){
    setDirection(port, OUTPUT);
    setPortRole(port, GPIO_ROLE);
    setOutputData(port, 0);
    setHighDriveStrength(port);
    setSlowSlewRate(port);
}



#define TFC_HBRIDGE_EN_LOC			(uint32_t)(1<<21)
#define TFC_HBRIDGE_FAULT_LOC     	(uint32_t)(1<<20)

#define TFC_HBRIDGE_ENABLE			GPIOE_PSOR = TFC_HBRIDGE_EN_LOC
#define TFC_HBRIDGE_DISABLE			GPIOE_PCOR = TFC_HBRIDGE_EN_LOC

#define TFC_DIP_SWITCH0_LOC			((uint32_t)(1<<2))
#define TFC_DIP_SWITCH1_LOC			((uint32_t)(1<<3))
#define TFC_DIP_SWITCH2_LOC			((uint32_t)(1<<4))
#define TFC_DIP_SWITCH3_LOC			((uint32_t)(1<<5))

#define TFC_PUSH_BUTT0N0_LOC		((uint32_t)(1<<13))
#define TFC_PUSH_BUTT0N1_LOC		((uint32_t)(1<<17))

#define TFC_BAT_LED0_LOC			((uint32_t)(1<<8))
#define TFC_BAT_LED1_LOC			((uint32_t)(1<<9))
#define TFC_BAT_LED2_LOC			((uint32_t)(1<<10))
#define TFC_BAT_LED3_LOC			((uint32_t)(1<<11))
//-------------  RGB LEDs ---------------------------------------------
#define RED_LED_LOC	         		((uint32_t)(1<<18))
#define GREEN_LED_LOC	         	((uint32_t)(1<<19))
#define BLUE_LED_LOC	         	((uint32_t)(1<<1))
#define PORT_LOC(x)        	        ((uint32_t)(1<<x))

#define RED_LED_OFF          		GPIOB_PSOR |= RED_LED_LOC
#define GREEN_LED_OFF	         	GPIOB_PSOR |= GREEN_LED_LOC
#define BLUE_LED_OFF	            GPIOD_PSOR |= BLUE_LED_LOC
#define RGB_LED_OFF	                RED_LED_OFF,GREEN_LED_OFF,BLUE_LED_OFF

#define RED_LED_TOGGLE          	GPIOB_PTOR |= RED_LED_LOC
#define GREEN_LED_TOGGLE	        GPIOB_PTOR |= GREEN_LED_LOC
#define BLUE_LED_TOGGLE	            GPIOD_PTOR |= BLUE_LED_LOC
#define RGB_LED_TOGGLE	            RED_LED_TOGGLE,GREEN_LED_TOGGLE,BLUE_LED_TOGGLE

#define RED_LED_ON          		GPIOB_PCOR |= RED_LED_LOC
#define GREEN_LED_ON	         	GPIOB_PCOR |= GREEN_LED_LOC
#define BLUE_LED_ON	                GPIOD_PCOR |= BLUE_LED_LOC
#define RGB_LED_ON	                RED_LED_ON,GREEN_LED_ON,BLUE_LED_ON

#define SW_POS 0x80  //PTD7
//---------------------------------------------------------------------
#define TFC_BAT_LED0_ON				GPIOB_PSOR = TFC_BAT_LED0_LOC
#define TFC_BAT_LED1_ON				GPIOB_PSOR = TFC_BAT_LED1_LOC
#define TFC_BAT_LED2_ON				GPIOB_PSOR = TFC_BAT_LED2_LOC
#define TFC_BAT_LED3_ON				GPIOB_PSOR = TFC_BAT_LED3_LOC

#define TFC_BAT_LED0_OFF			GPIOB_PCOR = TFC_BAT_LED0_LOC
#define TFC_BAT_LED1_OFF			GPIOB_PCOR = TFC_BAT_LED1_LOC
#define TFC_BAT_LED2_OFF			GPIOB_PCOR = TFC_BAT_LED2_LOC
#define TFC_BAT_LED3_OFF			GPIOB_PCOR = TFC_BAT_LED3_LOC

#define TFC_BAT_LED0_TOGGLE			GPIOB_PTOR = TFC_BAT_LED0_LOC
#define TFC_BAT_LED1_TOGGLE			GPIOB_PTOR = TFC_BAT_LED1_LOC
#define TFC_BAT_LED2_TOGGLE			GPIOB_PTOR = TFC_BAT_LED2_LOC
#define TFC_BAT_LED3_TOGGLE			GPIOB_PTOR = TFC_BAT_LED3_LOC

#define TFC_PUSH_BUTTON_0_PRESSED	((GPIOC_PDIR&TFC_PUSH_BUTT0N0_LOC)>0)
#define TFC_PUSH_BUTTON_1_PRESSED	((GPIOC_PDIR&TFC_PUSH_BUTT0N1_LOC)>0)
