#include "app.h"

#include <stdio.h>

#include <stdlib.h>

#define BUFFER_SIZE 10

void receiveFile(char * fName) {

//  if (fileCount == BUFFER_SIZE){
//	  free(pFiles[BUFFER_SIZE - 1] -> name);
//	  free(pFiles[BUFFER_SIZE - 1] -> content);
//	  free(pFiles[BUFFER_SIZE - 1]);
//  }
  // Allocating first place in files DS.
  int i;
  if (fileCount) {
    for (i = fileCount - 2; i >= 0; i--) {
      pFiles[i + 1] = pFiles[i];
    }
  }

  pFile * file = (pFile * ) malloc(sizeof(pFile));
  file -> size = currentFileSize;
  int fileNameLen = strlen(fName);
  file -> name = (char * ) malloc(strlen(fName));

  strcpy(file -> name, fName);

  file -> content = (char * ) malloc(file -> size);

  pFiles[0] = file;
  tempFile[0] = receivedByte; // Last received byte should be the first byte of the file.

  int j;
  for (j = 0; j < file -> size; j++)
    (file -> content)[j] = tempFile[j];

  fileCount = fileCount < BUFFER_SIZE ? fileCount + 1 : fileCount;

  readFileName = 0;
  enable_irq(INT_UART0 - 16); // Enable UART0 interrupt
  readState = 0;
  readMsgSize = 0;
  msgSize = 0;
  idx = 0;
  msgDisplayed = 0;
}

void extractFileSize(const int msgSize) {
  int i;
  char tempFileSize[4] = {0};
  
  
  for (i = 0; i < 4; i++) {
    tempFileSize[i] = message[i + msgSize - 4];
    message[i + msgSize - 4] = i == 0 ? ' ' : '\0';
  }
  
  currentFileSize = atoi(tempFileSize);

}

void filesScrollMenu() {
  
  static int scrollCounter = 0;
  
  int firstFileIndex = scrollCounter;
  currentPointedFileIndex  = firstFileIndex;
  
  scrollCounter = (++scrollCounter) % (fileCount-1);
  int secondFileIndex = scrollCounter;
  
  char str1[6];
  my_itoa(pFiles[firstFileIndex] -> size, str1);
  strcat(str1, "B\0");
  
  char str2[6];
  my_itoa(pFiles[secondFileIndex] -> size, str2);
  strcat(str2, "B\0");
  
  char firstFileName[MAX_LINE];
  char secondFileName[MAX_LINE];
//  int firstFileNameLen = strlen(pFiles[firstFileIndex] -> name);
//  int secondFileNameLen = strlen(pFiles[secondFileIndex] -> name);
  
  strcpy(firstFileName, pFiles[firstFileIndex] -> name);
  strcat(firstFileName, str1);
  
  strcpy(secondFileName, pFiles[secondFileIndex] -> name);
  strcat(secondFileName, str2);
  
  int len1 = strlen(firstFileName);
  int len2 = strlen(secondFileName);
  lcd_printFirstLine(firstFileName);
  lcd_printSecondLine(secondFileName);
}


char * my_itoa(const int num, char * str) {
  if (str == NULL) {
    return NULL;
  }
  sprintf(str, "%d", num);
  return str;
}
