#include "TFC.h"

#include "BoardSupport.h"
#include "mcg.h"
#include "MKL25Z4.h"

#define MUDULO_REGISTER  0x2EE0

// set I/O for switches and LEDs
void InitGPIO()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;

}
//-----------------------------------------------------------------
// DipSwitch data reading
//-----------------------------------------------------------------
uint8_t TFC_GetDIP_Switch()
{
	uint8_t DIP_Val=0;

	DIP_Val = (GPIOC_PDIR>>4) & 0xF;

	return DIP_Val;
}