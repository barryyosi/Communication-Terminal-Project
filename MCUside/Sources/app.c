#include "app.h"

void receiveFile(char* fName){
    
    pFile file;
    file.name = fName;
    file.size = currentFileSize;
    tempFile[0] = receivedByte;		// Last received byte should be the first byte of the file.
    file.content = (char*)malloc(file.size);
    int j;
    for(j = 0; j < file.size; j++)
    	file.content[j] = tempFile[j];
    
    // Allocating first place in files DS.
    int i;
    if(fileCount){
        for (i = fileCount - 1; i > 0; i--){
            if(i == FILES_LIMIT - 1)
                continue;
            pFiles[i+1] = pFiles[i];
        }
    }
    pFiles[0] = &file;
    fileCount++;
    
    readFileName = 0;
    enable_irq(INT_UART0-16);						// Enable UART0 interrupt
    readState = 0;
	readMsgSize = 0;
	msgSize = 0;
	idx = 0;
	msgDisplayed = 0;
}


void extractFileSize(const int msgSize){
	int i;
	char tempFileSize[4] = {0};
	
	for(i = 0; i < 4; i++){
		tempFileSize[i] = message[i + msgSize - 4];
		message[i + msgSize - 4] = ' ';
	}
	currentFileSize = atoi(tempFileSize);
	
}
