#include "TFC.h"
#include "app_FSM_handler.h"
#include "api.h"
#include "arm_cm0.h"

#define CORE_CLOCK 48000000

const char receiveFileMsg[] = "received";
const char sendFileMsg[] = "being sent";

int main(void) {
	dmaIrqFlag = 0;
	fileCount = 0;
	readState = 0;
	readMsgSize = 0;
	readMessage = 0;
	msgSize = 0;
	idx = 0;
	terminalConfigReady = 0;
	readBaudRateReady = 0;
	send_recv_flag = 0;
	inits();
	
	while (1) {
		wait();
		updateState(tempState);
		if (!msgDisplayed) {
			if (getState() == terminalConfigMode && readBaudRateReady) {
				int baudRate = atoi(message);
				Uart0_Br_Sbr(CORE_CLOCK / 2 / 1000, atoi(message));
			} else {
				lcd_printNewLn(message);
				if (readFileName) {
					lcd_printNewLn(fileName);
					int i;
					if(!send_recv_flag){
						lcd_printSecondLine(receiveFileMsg);
						readFileName = 0;
						enable_irq(INT_UART0 - 16); // Enable UART0 interrupt
						readState = 0;
						readMsgSize = 0;
						msgSize = 0;
						idx = 0;
						msgDisplayed = 0;

					}
					else{
						lcd_printSecondLine(sendFileMsg);
						UART_sendFile(sentFileIndex);
						send_recv_flag = 0;
					}
				}
			}
		}
	
		if (msgDisplayed && readFileName) {

		}
		msgDisplayed = 1;
	}

	return 0;
}

//-----------------------------------------------------------------
//  UART0 - ISR
//-----------------------------------------------------------------

