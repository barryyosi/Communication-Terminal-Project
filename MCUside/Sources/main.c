//Ex1: send a string when receiving 'u' character

//#include "derivative.h" /* include peripheral declarations */

#include "TFC.h"
#include "app_FSM_handler.h"
#include "api.h"
#include "arm_cm0.h"

const char transferMsg[] = "received";
int main(void){
	dmaIrqFlag = 0;
	fileCount = 0;
	inits();
	
	while(1){
		wait();
		updateState(tempState);
		if (!msgDisplayed){
			lcd_printNewLn(message);
			if (readFileName){
				lcd_printLine2(transferMsg);
			}
		}
		else if (msgDisplayed && readFileName){
			receiveFile(fileName);
			// Put in DMA handler readFileName = 0;
		}
		msgDisplayed = 1;
	}
		

	return 0;
}

//-----------------------------------------------------------------
//  UART0 - ISR
//-----------------------------------------------------------------

