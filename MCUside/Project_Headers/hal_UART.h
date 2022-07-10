#ifndef TFC_UART_H_
#define TFC_UART_H_

void Uart0_Br_Sbr(int sysclk, int baud);
void InitUARTs();
void UART0_IRQHandler();
void UART_PrintLine(char* str);
void UART_ReadLine(char* str, int strLen);
void UART_PrintMenu();
void printLater(char * str);

#endif /* TFC_UART_H_ */
