#ifndef CONNECTION_MAP_H_
#define CONNECTION_MAP_H_

#include "TFC.h"


//this file describe the connection of extended board ports to the MKL25z4 ports


// #define P1_0  {BASE_D, 5}
// #define P1_1  {BASE_D, 6}
// #define P1_2  {BASE_D, 7}
// #define P1_3  {BASE_B, 3}
// #define P1_4  {BASE_C, 12}
// #define P1_5  {BASE_C, 13}
// #define P1_6  {BASE_C, 16}
// #define P1_7  {BASE_C, 17}

// #define P2_0  {BASE_C, 7}
// #define P2_1  {BASE_C, 0}
// #define P2_2  {BASE_C, 3}
// #define P2_3  {BASE_C, 4}
// #define P2_4  {BASE_D, 1}
// #define P2_5  {BASE_C, 6}
// #define P2_6  {BASE_C, 10}
// #define P2_7  {BASE_C, 11}

#define RGB_LED_BLUE_PORT   {BASE_D, 1}
#define RGB_LED_RED_PORT    {BASE_B, 18}
#define RGB_LED_GREEN_PORT  {BASE_B, 19}

typedef enum{
    RGB_LED_BLUE = 0,
    RGB_LED_RED  ,
    RGB_LED_GREEN,
    RGB_LED_NUM
} RGB_LED;
extern Port RGB_leds[RGB_LED_NUM];


extern Port PushButtons[4];
extern Port Keypad[8];
extern Port Keypad_IRQ;
extern Port Switches[4];
extern Port Leds[8];
extern Port InputCapture;
extern Port OutputCapture;
extern Port potentiometer;
extern Port lcdPorts[7];
#endif
