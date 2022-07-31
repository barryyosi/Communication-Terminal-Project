#ifndef API_LCD
#define API_LCD

#include "TFC.h"

void lcd_printInt(int number);
void lcd_printNewLn(const char * s);
void lcd_printLine2(const char * s);
void lcd_puts(const char * s);
void lcd_puts2(const char * s);
void lcd_putchar2(unsigned char c);
#endif
