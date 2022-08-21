#include "app.h"

#include <stdio.h>

#include <stdlib.h>

#define BUFFER_SIZE 10

void receiveFile(char * fName) {

  int i;
  if (fileCount) {
    if(fileCount > 9) i = 8;  // TODO: check
    else i = fileCount - 1;
    for (; i >= 0; i--) {
      pFiles[i + 1] = pFiles[i];
    }
  }

  pFiles[0].size = currentFileSize;
  int fileNameLen = strlen(fName);

  strcpy(pFiles[0].name, fName);
  pFiles[0].name[fileNameLen] = '\0';

  tempFile[0] = receivedByte; // Last received byte should be the first byte of the file.

  memset( & (pFiles[0].content), 0, pFiles[0].size);
  int j;

  for (j = 0; j < MAX_FILE_SIZE; j++)
    (pFiles[0].content)[j] = tempFile[j];

  pFiles[0].content[pFiles[0].size] = '\0';

  fileCount = fileCount < BUFFER_SIZE ? fileCount + 1 : fileCount;

}

void extractFileSize(const int msgSize) {
  int i;
  char tempFileSize[4] = {
    0
  };

  for (i = 0; i < 4; i++) {
    tempFileSize[i] = message[i + msgSize - 4];
    message[i + msgSize - 4] = i == 0 ? ' ' : '\0';
  }

  currentFileSize = atoi(tempFileSize);

}

void filesScrollMenu() {

  static int scrollCounter = 0;

  int firstFileIndex = scrollCounter, secondFileIndex;
  char firstFileName[MAX_LINE];
  char secondFileName[MAX_LINE];
  char fileSize[6];

  currentPointedFileIndex = firstFileIndex;

  if(fileCount == 0){
    lcd_printFirstLine("no files");
  }
  else{
    strcpy(firstFileName, pFiles[firstFileIndex].name);
    my_itoa(pFiles[firstFileIndex].size, fileSize);
    strcat(firstFileName, fileSize);
    strcat(firstFileName, "B\0");
    lcd_printFirstLine(firstFileName);

    if(fileCount >= 2){
      scrollCounter = (++scrollCounter) % (fileCount);
      secondFileIndex = scrollCounter;

      strcpy(secondFileName, pFiles[secondFileIndex].name);
      my_itoa(pFiles[secondFileIndex].size, fileSize);
      strcat(secondFileName, fileSize);
      strcat(secondFileName, "B\0");
      lcd_printSecondLine(secondFileName);
    }
  }
}

char * my_itoa(const int num, char * str) {
  if (str == NULL) {
    return NULL;
  }
  sprintf(str, "%d", num);
  return str;
}