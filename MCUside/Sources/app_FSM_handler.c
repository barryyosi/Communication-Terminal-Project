#include "app_FSM_handler.h"
#include "BoardSupport.h"
#include "MKL25Z4.h"
#include "hal_UART.h"
#include "hal_ADC_DAC.h"
#include "hal_LCD.h"
#include "hal_timers.h"



FSMstate sysState = sleepMode;//, g_newState = state0;

/*
int X = 500;

int upCount = 0;
int downCount = 65535;

int getX(){return X;}
void setX(int newX){
    X = newX;
    updatePIT(X);
}


int getUpCountAndInc(){return upCount++;}
int getDownCountAndDecr(){return downCount--;}

void resetUpCount(){upCount = 0;}
void resetDownCount(){downCount = 65535;}*/
/*
// void handleStateChangeIfNeeded(){
//     if(g_state == g_newState) return;

//     exitState(g_state);
//     g_state = g_newState;
//     enterState(g_state);
// }
*/
/*
void setNewState(int newState){
    if(0 <= newState && newState < numOfStates)
        g_newState = newState;
    else
        while (1);

}
*/
FSMstate getState(){
    return sysState;
}

void enterState(FSMstate state){
    switch(state){
        case sleepMode:
        {}break;

        case chatMode:
        {}break;

        case fileTransferMode:
        {}break;

        case terminalConfigMode:
        {}break;
/*
    //     case state1:
    //     case state2:
    //     case state3:
    //     {
	// 		startPitCount();
    //         break;
    //     }
    //     case state5:{
    //         enableADC();
    //         break;
    //     }

    //     case state6:
    //     {
    //         resetDownCount();
	// 		resetUpCount();
	// 		break;
    //     }
    //     case state7:
    //     {
    //         UART_PrintMenu();
    //         setNewState(state0);
	// 		break;
    //     }
    //     case state8:
    //     {
	//         enable_irq(INT_PORTD-16);
	// 		break;
    //     }
    // }
    */
}
}

void exitState(FSMstate state){
    lcd_clear();
    switch(state){
        case sleepMode:
        {}break;

        case chatMode:
        {}break;

        case fileTransferMode:
        {}break;

        case terminalConfigMode:
        {}break;
/*

		/*case state1:
        case state2:
        case state3:
        {
			stopPitCount();
            break;
        }
        case state5:
            disableADC();
            break;

        case state8:
	        disable_irq(INT_PORTD-16);
		default:
			break;*/
    }
}
