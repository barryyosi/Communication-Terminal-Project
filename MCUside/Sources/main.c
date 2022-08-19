#include "TFC.h"
#include "app_FSM_handler.h"
#include "api.h"
#include "arm_cm0.h"

#define CORE_CLOCK 48000000

const char transferMsg[] = "received";
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
	inits();
	// TODO - process file size before file is received.
	currentFileSize = 1000;
	pFile aFile, bFile, cFile;
	aFile.content = "aaaaaa";
	bFile.content = "bbbbbbbbb";
	cFile.content = "cccccccccccccccc";

	aFile.name = "aFile.txt";
	bFile.name = "bFile.txt";
	cFile.name = "cFile.txt";

	aFile.size = 6;
	bFile.size = 9;
	cFile.size = 16;

	pFiles[0] = &aFile;
	pFiles[1] = &bFile;
	pFiles[2] = &cFile;
	fileCount = 3;
	while (1) {
		wait();
		updateState(tempState);
		if (!msgDisplayed) {
			if (getState() == terminalConfigMode && readBaudRateReady) {
				int baudRate = atoi(message);
				Uart0_Br_Sbr(CORE_CLOCK / 2 / 1000, atoi(message));
			} else {
				lcd_printNewLn(message);
				if (readFileName) {	// Add flag to not show this when file is being transferred.
					lcd_printNewLn(fileName);
					lcd_printSecondLine(transferMsg);
					receiveFile(fileName);
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

