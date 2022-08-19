
#ifndef TFC_H_
#define TFC_H_
#define MAX_MSG 32
#define MAX_LINE 16
#define FILES_LIMIT 10
#define MAX_FILE_SIZE 1000
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "arm_cm0.h"
#include "api_general_macros.h"
#include "bsp_gpio.h"
#include "bsp_connection_map.h"
#include "MKL25Z4.h"
#include "hal_UART.h"
#include "hal_keypad.h"
#include "hal_PB_SW_LED_RGB.h"
#include "hal_dma.h"
#include "hal_lcd.h"
#include "api_lcd.h"
#include "app_FSM_handler.h"
#include "app.h"

char receivedByte;
int readState;
int readMsgSize;
int readMessage;
short msgSize;
static int idx;

int keypadPressCounters[16];	// Used to count presses on keypad keys, in order to iterate over character options.
int mcuTyping;					// Flag indicating ongoing type on mcu.
char mcuMessage[MAX_MSG];   	// Message to be sent to PC
int idxInMcuMessage;
char currentMessageChar;		// Holds the the char to be appended to the message.

char message[MAX_MSG];      	// Received message from PC
int msgDisplayed;		    	// Flag notes whether the message was already displayed or not.
int tempState;

char fileName[MAX_MSG];      	// Received fileName from PC
int fileTransferReady;
int readFileName;
int dmaIrqFlag;

typedef struct pFile{
    int size;
    char* name;
    char* content;
} pFile;

pFile* pFiles[FILES_LIMIT];
// char* files[20];
// char* fileNames[20];
char tempFile[MAX_FILE_SIZE];
char tempFile3[MAX_FILE_SIZE];
char* tempFile2;
int fileSizes[20];
int fileCount;
int currentFileSize;
int currentPointedFileIndex;

int terminalConfigReady;
int readBaudRateReady;
#endif /* TFC_H_ */
