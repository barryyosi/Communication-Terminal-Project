#ifndef _LCD_H_
#define _LCD_H_

#include "TFC.h"


// #define CHECKBUSY	1  // using this define, only if we want to read from LCD

#ifdef CHECKBUSY
	#define	LCD_WAIT lcd_check_busy()
#else
	#define LCD_WAIT DelayMs(5)
#endif

#define	lcd_cursor(x)			  lcd_cmd(((x)&0x7F)|RW_BIT)
#define lcd_clear()				  lcd_cmd(0x01)
#define lcd_goto_start(x)		  lcd_cmd(0x80)
#define lcd_goto(x)				  lcd_cmd(0x80+(x))
#define lcd_cursor_right()		  lcd_cmd(0x14)
#define lcd_cursor_left()		  lcd_cmd(0x10)
#define lcd_display_shift()		  lcd_cmd(0x1C)
#define lcd_home()				  lcd_cmd(0x02)
#define cursor_off()              lcd_cmd(0x0C)
#define cursor_on()               lcd_cmd(0x0F)
#define lcd_function_set()        lcd_cmd(0x3C) // 8bit,two lines,5x10 dots
#define lcd_go_to_line2()         lcd_cmd(0xC0)
#define lcd_goto_in_second_line(x) lcd_cmd(0xC0 + (x))

#define setEntryMode()			  lcd_cmd(0x6);  //Entry Mode
#define cursorBlink()			  lcd_cmd(0xF);  //Display On, Cursor On, Cursor Blink

void lcd_putchar(unsigned char);
void lcd_puts(const char * s);
void lcd_printNewLn(const char * s);
void initLCD();

///////////////////////////////////////////////////////////////////////////


/*
 * Connections: 		PB to PTD7
 * 				connect LCD_GND to KL25Z_GND
 * 				connect LCD_5v to KL25Z_5v
 * 				LCD brightness to potentiometer's middle leg
 * 				LCD RS to PTE3
 * 				LCD RW to PTE4
 * 				LCD E to PTE5
 * 				LCD DB4-DB7 to PTB0-PTB3
 *
 */

//extern Port lcd[7];
#define P1OUT GPIOB_PDOR
#define P1DIR GPIOB_PDDR

#define RS_PCR PORTE_PCR3
#define RW_PCR PORTE_PCR4
#define EN_PCR PORTE_PCR5

#define LCD_DATA_PCR4	PORTB_PCR0
#define LCD_DATA_PCR5	PORTB_PCR1
#define LCD_DATA_PCR6	PORTB_PCR2
#define LCD_DATA_PCR7	PORTB_PCR3

#define RS_BIT BIT(3)
#define RW_BIT BIT(4)
#define EN_BIT BIT(5)
/*----------------------------------------------------------
  CONFIG: change values according to your port pin selection
------------------------------------------------------------*/
#define LCD_EN(a)	(!a ? (GPIOE_PDOR &=~EN_BIT) : (GPIOE_PDOR|=EN_BIT)) // P1.5 is lcd enable pin
#define LCD_EN_DIR(a)	(!a ? (GPIOE_PDDR&=~EN_BIT) : (GPIOE_PDDR|=EN_BIT)) // P1.5 pin direction

#define LCD_RS(a)	(!a ? (GPIOE_PDOR&=~RS_BIT) : (GPIOE_PDOR|=RS_BIT)) // P1.6 is lcd RS pin
#define LCD_RS_DIR(a)	(!a ? (GPIOE_PDDR&=~RS_BIT) : (GPIOE_PDDR|=RS_BIT)) // P1.6 pin direction

#define LCD_RW(a)	(!a ? (GPIOE_PDOR&=~RW_BIT) : (GPIOE_PDOR|=RW_BIT)) // P1.7 is lcd RW pin
#define LCD_RW_DIR(a)	(!a ? (GPIOE_PDDR&=~RW_BIT) : (GPIOE_PDDR|=RW_BIT)) // P1.7 pin direction

#define LCD_DATA_OFFSET 0x00 //data pin selection offset for 4 bit mode, variable range is 0-4, default 0 - Px.0-3, no offset

#define LCD_DATA_WRITE	GPIOB_PDOR
#define LCD_DATA_DIR	GPIOB_PDDR
#define LCD_DATA_READ	GPIOB_PDIR
/*---------------------------------------------------------
  END CONFIG
-----------------------------------------------------------*/
#define FOURBIT_MODE	0x0
#define EIGHTBIT_MODE	0x1
#define LCD_MODE        FOURBIT_MODE

#define OUTPUT_PIN      1
#define INPUT_PIN       0
#define OUTPUT_DATA     (LCD_MODE ? 0xFF : (0x0F << LCD_DATA_OFFSET))
#define INPUT_DATA      0x00

#define LCD_STROBE_READ(value)	LCD_EN(1), \
				asm("nop"), asm("nop"), \
				value=LCD_DATA_READ, \
				LCD_EN(0)
void lcd_SetOutPut4bit(unsigned char c);
void lcd_cmd(unsigned char);
void initLCD_pins();
void lcd_strobe();

#endif






