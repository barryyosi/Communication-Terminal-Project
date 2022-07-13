/*
 * TFC.h
 *
 *  Created on: Apr 13, 2012
 *      Author: emh203
 */

#ifndef TFC_H_
#define TFC_H_
#define MAX_MSG 32
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "arm_cm0.h"
#include "api_general_macros.h"
#include "bsp_connection_map.h"
#include "MKL25Z4.h"
#include "api_lcd.h"
#include "hal_UART.h"
#include "app_FSM_handler.h"

// int dataready = 0;  		//flag which indicates if data received from UART is ready to be used 

char message[MAX_MSG];       // Received message from pc
int msgDisplayed;		// Flag notes whether the message was already displayed or not.
int tempState;
//int msgSize;
#endif /* TFC_H_ */
