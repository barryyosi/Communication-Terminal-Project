//Ex1: send a string when receiving 'u' character

//#include "derivative.h" /* include peripheral declarations */

#include "TFC.h"
#include "app_FSM_handler.h"
#include "api.h"
#include "arm_cm0.h"

int main(void){
	inits();

	while(1){
		wait();
		handleStateChangeIfNeeded();
	}
	return 0;
}

//-----------------------------------------------------------------
//  UART0 - ISR
//-----------------------------------------------------------------

