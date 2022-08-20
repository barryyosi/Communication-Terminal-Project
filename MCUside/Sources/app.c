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
    for (i = fileCount - 1; i >= 0; i--) {
      pFiles[i + 1] = pFiles[i];
    }
  }


  pFiles[0].size = currentFileSize;
  int fileNameLen = strlen(fName);
//  file -> name = (char * ) malloc(strlen(fName));
  
  strcpy(pFiles[0].name, fName);
  pFiles[0].name[fileNameLen] = '\0';
  
  //  file -> content = (char * ) malloc(file -> size + 1);

 tempFile[0] = receivedByte; // Last received byte should be the first byte of the file.
  
//  strcpy(file -> content, tempFile);
//  file->content[file->size] = "\0";
  memset(&(pFiles[0].content), 0, pFiles[0].size);
   int j;
  // int fileSize = file->size;
   for (j = 0; j < MAX_FILE_SIZE; j++)
     (pFiles[0].content)[j] = tempFile[j];

//  strcpy(pFiles[0].content, tempFile);
  pFiles[0].content[pFiles[0].size] = '\0';
  
  fileCount = fileCount < BUFFER_SIZE ? fileCount + 1 : fileCount;

//  readFileName = 0;
  
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
  
  scrollCounter = (++scrollCounter) % (fileCount);
  int secondFileIndex = scrollCounter;
  
  char str1[6];
  my_itoa(pFiles[firstFileIndex].size, str1);
  strcat(str1, "B\0");
  
  char str2[6];
  my_itoa(pFiles[secondFileIndex].size, str2);
  strcat(str2, "B\0");
  
  char firstFileName[MAX_LINE];
  char secondFileName[MAX_LINE];
//  int firstFileNameLen = strlen(pFiles[firstFileIndex] -> name);
//  int secondFileNameLen = strlen(pFiles[secondFileIndex] -> name);
  
  strcpy(firstFileName, pFiles[firstFileIndex].name);
  strcat(firstFileName, str1);
  
  strcpy(secondFileName, pFiles[secondFileIndex].name);
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

