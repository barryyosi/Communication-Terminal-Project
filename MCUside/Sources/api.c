#include "TFC.h"
#include "api.h"
#include "BoardSupport.h"
#include "hal_timers.h"
#include "hal_UART.h"
#include "arm_cm0.h"
#include "app_FSM_handler.h"
#include "hal_LCD.h"
#include "hal_PB_SW_LED_RGB.h"
#include "hal_ADC_DAC.h"

void inits() {

	ClockSetup();
	InitGPIO();
	
	initKeypad();
	initPushButton(0);
	
	//InitPIT(getX());
	InitUARTs();
	initLCD();
	initRGBLed();
	InitADCs();
	InitPIT(1500);		// Setting pit for 2sec delay in order to allow switching between key character options.
	
	initDMA();
	mcuTyping = 0;
	
	enable_irq(INT_PORTD-16); // Enable Interrupts 
	set_irq_priority (INT_PORTD-16,0);  // Interrupt priority = 0 = max
	EnableInterrupts();
}
