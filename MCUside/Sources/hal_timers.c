#include "hal_timers.h"
#include "MKL25Z4.h"
#include "mcg.h"
#include "app_FSM_handler.h"
#include "hal_PB_SW_LED_RGB.h"
#include "api_LCD.h"

/*void PIT_IRQHandler(){
        switch(getState()){
        case state1:
            toggleRGB();
            break;
        case state2:
            lcd_printInt(getUpCountAndInc());
            break;
        case state3:
            lcd_printInt(getDownCountAndDecr());
            break;
        case state5:
        {
			//read potentiometer

            //ADC0_SC1A = POT_ADC_CHANNEL | ADC_SC1_AIEN_MASK;  //POT channel is SE0 , ADC interrupt is enabled.
            break;
        }
        default:
            break;
    }
	PIT_TFLG0 = PIT_TFLG_TIF_MASK; //clear the Pit 0 Irq flag
}
*/

//-----------------------------------------------------------------
// TPMx - Initialization
//-----------------------------------------------------------------
#define MUDULO_REGISTER  0x2EE0
void InitTPM(char x){  // x={0,1,2}
	switch(x){
	case 0:
		TPM0_SC = 0; // to ensure that the counter is not running
		TPM0_SC |= TPM_SC_PS(3)+TPM_SC_TOIE_MASK; //Prescaler =128, up-mode, counter-disable
		TPM0_MOD = MUDULO_REGISTER; // PWM frequency of 250Hz = 24MHz/(8x12,000)
		TPM0_C1SC |= TPM_CnSC_MSB_MASK + TPM_CnSC_ELSB_MASK + TPM_CnSC_CHIE_MASK;
		TPM0_C1V = 0xFFFF;
		TPM0_CONF = 0;
		break;
	case 1:

		break;
	case 2:
		TPM2_SC = 0; // to ensure that the counter is not running
		TPM2_SC |= TPM_SC_PS(3)+TPM_SC_TOIE_MASK; //Prescaler =128, up-mode, counter-disable
		TPM2_MOD = MUDULO_REGISTER; // PWM frequency of 250Hz = 24MHz/(8x12,000)
		TPM2_C0SC |= TPM_CnSC_MSB_MASK + TPM_CnSC_ELSB_MASK + TPM_CnSC_CHIE_MASK;
		TPM2_C0V = 0xFFFF;
		TPM2_C1SC |= TPM_CnSC_MSB_MASK + TPM_CnSC_ELSB_MASK + TPM_CnSC_CHIE_MASK;
		TPM2_C1V = 0xFFFF;
		TPM2_CONF = 0;
		break;
	}
}
//-----------------------------------------------------------------
// TPMx - Clock Setup
//-----------------------------------------------------------------
void ClockSetup(){

	    pll_init(8000000, LOW_POWER, CRYSTAL,4,24,MCGOUT); //Core Clock is now at 48MHz using the 8MHZ Crystal

	    //Clock Setup for the TPM requires a couple steps.
	    //1st,  set the clock mux
	    //See Page 124 of f the KL25 Sub-Family Reference Manual
	    SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;// We Want MCGPLLCLK/2=24MHz (See Page 196 of the KL25 Sub-Family Reference Manual
	    SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);
	    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1); //We want the MCGPLLCLK/2 (See Page 196 of the KL25 Sub-Family Reference Manual
		//Enable the Clock to the TPM0 and PIT Modules
		//See Page 207 of f the KL25 Sub-Family Reference Manual
		SIM_SCGC6 |= SIM_SCGC6_TPM0_MASK + SIM_SCGC6_TPM2_MASK;
	    // TPM_clock = 24MHz , PIT_clock = 48MHz

}
//-----------------------------------------------------------------
// PIT - Initialisation
//-----------------------------------------------------------------
void InitPIT(uint32_t X){
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK; //Enable the Clock to the PIT Modules
	// Timer 0
	PIT_LDVAL0 = (X * 0x0000BB80); // setup timer 0 for 1msec counting period
	PIT_TCTRL0 = PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK; //enable PIT0 and its interrupt
	PIT_MCR |= PIT_MCR_FRZ_MASK; // stop the pit when in debug mode
	enable_irq(INT_PIT-16); //  //Enable PIT IRQ on the NVIC
	set_irq_priority(INT_PIT-16,0);  // Interrupt priority = 0 = max
}

void updatePIT(uint32_t X){
	PIT_LDVAL0 = (X * 0x0000BB80); // setup timer 0 for 1msec counting period
}


void startPitCount(){PIT_MCR &= ~PIT_MCR_MDIS_MASK;} //Enable the PIT module;
void stopPitCount() {PIT_MCR |=  PIT_MCR_MDIS_MASK;} //disable the PIT module;
