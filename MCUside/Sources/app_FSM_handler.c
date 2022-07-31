#include "app_FSM_handler.h"
#include "BoardSupport.h"
#include "MKL25Z4.h"
#include "hal_UART.h"
#include "hal_ADC_DAC.h"
#include "hal_LCD.h"
#include "hal_timers.h"
#include "app_FSM_handler.h"


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

void handleDevicesInterrupt(DeviceId deviceId){
	char keyPressed;
	char messagePrefix[] = "MCU:";
	int messageSize;
    switch (deviceId)
    {
/*

        // case PUSH_BUTTON_1:
        //     state = state2;

        // 	break;

        // case PUSH_BUTTON_2:
        //     state = state3;
		// 	break;

        // case PUSH_BUTTON_3:
        //     break;

        // case SWITCH_0:
        // case SWITCH_1:
        // case SWITCH_2:
        // case SWITCH_3:
		// 	//getSwitchesState();
        // 	break;
*/
        case KEYPAD_IRQ:
			if (getState() == chatMode){
				if (mcuTyping != 1){
					lcd_printNewLn(messagePrefix);
					mcuTyping = 1;
					idxInMcuMessage = 0;
				}
                keyPressed = keypad_scan();		        // Scanning the keypad & saving the pressed key
                clearIRQFlag(Keypad_IRQ);
                if(keyPressed != 'z'){					// Avoiding undefined char.
					lcd_putchar2(keyPressed);
					currentMessageChar = keyPressed;
                }                                                                                                                                                                                            
			    pitEnable();
			    
            }
			break;
			
		 case PUSH_BUTTON_0:
			 if (getState() == chatMode){
				 // TODO - Send current message to PC
				 mcuMessage[idxInMcuMessage - 1] = currentMessageChar;
				//  messageSize = idxInMcuMessage - 
                //  mcuMessage[0]
                 mcuMessage[idxInMcuMessage] = '$';

				 uart0_putstr(mcuMessage);
				 memset(&mcuMessage[0], 0, sizeof(mcuMessage));
				//  idxInMcuMessage = 0;
				 lcd_clear();                                                                                                                                                                                                                                                                  
				 mcuTyping = 0;
			 }
			 break;                                     

		default:
			break;

    }
	// if(PUSH_BUTTON_0 <= deviceId && PUSH_BUTTON_3 >= deviceId)
	// 	enterState(state);

}


void setState(FSMstate argState){ sysState = argState;}

FSMstate getState(){ return sysState; }

void updateState(FSMstate argState){
    if(getState() != argState)
//    	if (getState() == fileTransferMode)		// Nullifying fileTransferReady flag, if no longer on fileTransferMode.
//    		fileTransferReady = 0;
    	exitState(getState());
        setState(argState);
        enterState(argState);
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
