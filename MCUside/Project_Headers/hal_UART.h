#ifndef TFC_UART_H_
#define TFC_UART_H_
#include "TFC.h"

void Uart0_Br_Sbr(int sysclk, int baud);
void InitUARTs();
void UART0_IRQHandler();
void UART_PrintLine(char* str);
void UART_ReadLine(char* str, int strLen);
void UART_PrintMenu();
void printLater(char * str);
char uart_getchar (UART_MemMapPtr channel);
void uart_putchar (UART_MemMapPtr channel, char ch);

#endif /* TFC_UART_H_ */
