#include "bsp_connection_map.h"
//this file describe the connection of extended board ports to the MKL25z4 ports



Port PushButtons[4] = {
                                {BASE_D, 5},
                                {BASE_D, 6},
                                {BASE_D, 7},
                                {BASE_D, 3}
                            };
Port Keypad[8] = {
								{BASE_C, 6}, 	// keypad col 1
								{BASE_C, 5}, 	// keypad col 2
								{BASE_C, 4},	// keypad col 3
								{BASE_C, 3}, 	// keypad col A
								{BASE_C, 11},   // keypad row 1
								{BASE_C, 10},	// keypad row 4
								{BASE_C, 9},	// keypad row 7
								{BASE_C, 8}		// keypad row F

						};
Port Keypad_IRQ =  {BASE_D, 0};

Port Switches[4]; //= {
                            //      P2_0,
                            //      P2_1,
                            //      P2_2,
                            //      P2_3
                            // };

Port Leds[8]; //= {
                            //     {BASE_E, 29}
                            //      P2_1,
                            //      P2_2,
                            //      P2_3,
                            //      P2_0,
                            //      P2_1,
                            //      P2_2,
                            //      P2_3
                            // };



Port RGB_leds[RGB_LED_NUM] = {
    RGB_LED_BLUE_PORT,
    RGB_LED_RED_PORT  ,
    RGB_LED_GREEN_PORT
};


Port lcdPorts[7] = {
	{BASE_B, 0},
	{BASE_B, 1},
	{BASE_B, 2},
	{BASE_B, 3},
	{BASE_E, 3},
	{BASE_E, 4},
	{BASE_E, 5}
};

Port potentiometer = {BASE_E, 29};
Port InputCapture;
Port OutputCapture;
