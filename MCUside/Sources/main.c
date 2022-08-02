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
	readState = 0;
	readMsgSize = 0;
	readMessage = 0;
	msgSize = 0;
	idx = 0;
	inits();
	// TODO - process file size before file is received.
	currentFileSize = 1000;
	while(1){
		wait();
		updateState(tempState);
		if (!msgDisplayed){
			lcd_printNewLn(message);
			if (readFileName){		// Add flag to not show this when file is being transferred.
				lcd_printNewLn(fileName);
				lcd_printLine2(transferMsg);
				receiveFile(fileName);
			}
		}
		if (msgDisplayed && readFileName){

			
		}
		msgDisplayed = 1;
	}
		

	return 0;
}

//-----------------------------------------------------------------
//  UART0 - ISR
//-----------------------------------------------------------------

