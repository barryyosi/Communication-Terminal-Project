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
	//InitPIT(getX());
	InitUARTs();
	initLCD();
	initRGBLed();
	InitADCs();

	initPushButton(0);

	EnableInterrupts();
}
