#include "TFC.h"
#include "MKL25Z4.h"
#include "app_FSM_handler.h"
#include "hal_UART.h"



#define SDA_SERIAL_BAUD 9600
#define CORE_CLOCK 48000000
#define MAX_STRING 1000

uint8_t string1[31];
char readStr[MAX_STRING] = {0};
char printStr[MAX_STRING] = {0};
int readStr_index = 0;
int printStr_in_index = 0;
int printStr_out_index = 0;

// TODO - validate
int readState = 0;
int readMessageSize = 0;
int readMessage = 0;
int messageSize;
char[] message = {0};
char* pMessage;


void UART0_IRQHandler(){
    static int intInput;
    if( UART0_S1 & UART_S1_RDRF_MASK ){ // RX buffer is full and ready for reading

	    printStr[printStr_in_index++] = readStr[readStr_index++] = UART0_D;
        // 1st implementation option - receving header bytes: systameState, message size
        if (!readState){
            if(sysState != atoi(UART0_D)){
                exitState(sysState);
                sysState = atoi(UART0_D);
                enterState(sysState);
            }
            else
                readState = 1;
            
        }
        else if (!readMessageSize)
        {
            messageSize = atoi(UART0_D);
            pMessage = (char*)malloc(messageSize);
            readMessageSize = 1;
        }else
        {
            static int currentlyReceivedBytes = 0;
            if(currentlyReceivedBytes < messageSize)
                pMessage[currentlyReceivedBytes++] = UART0_D;
            else{
                currentlyReceivedBytes = 0;
                readState = 0;
                readMessageSize = 0;
                readStr = *(pMessage);
                free(pMessage);
            }
        }
        
        

        // 2nd implementation option - incase message is terminated with /r or /n.
	    if (readStr[readStr_index-1] == '\r'){
            printStr[printStr_in_index++]   = readStr[readStr_index++]  = '\n';
            readStr_index = 0;

            // handle state
            intInput = atoi(readStr);
            if(getState() == state4){
                if(intInput <= 0) printLater(errorMsg);
                else{
                    setX(intInput);
                    setNewState(0);
                }
            } else {
                if(intInput == 9) setNewState(0);
                else if(intInput <= 0 || intInput >= numOfStates) printLater(errorMsg);
                else setNewState(intInput);
            }
	    }
        UART0_C2 |= UART_C2_TIE_MASK;   // enable transmit
	}
	else if( UART0_S1 & UART_S1_TDRE_MASK ){ // TX buffer is empty and ready for sending
		UART0_D = printStr[printStr_out_index++];
		if (printStr_in_index <= printStr_out_index){                  // TX over?
            printStr_in_index = printStr_out_index = 0;
		    UART0_C2 &= ~UART_C2_TIE_MASK;
		}

	}
}

void printLater(char * str){
    int i = 0;
    for(; str[i] != '\0'; i++)
        printStr[printStr_in_index++] = str[i];
    UART0_C2 |= UART_C2_TIE_MASK;   // enable transmit
}

void UART_PrintMenu(){
    static char menu[] =
        "1. Blink RGB LED, color by color with delay of X[ms] \r\n"
        "2. Count up onto LCD screen with delay of X[ms]      \r\n"
        "3. Count down onto LCD screen with delay of X[ms]    \r\n"
        "4. Get delay time X[ms]:                             \r\n"
        "5. Potentiometer 3-digit value [v]                   \r\n"
        "6. Clear LCD screen                                  \r\n"
        "7. Show menu                                         \r\n"
        "8. Sleep                                             \r\n";
    UART_PrintLine(menu);
}

void UART_PrintLine(char* str){
    int len;
    while(printStr_in_index != 0 || printStr_out_index != 0) wait();
    for(len = 0; str[len] != '\0'; len++){
        printStr[len] = str[len];
    }
    printStr[len] = '\0';
    printStr_out_index = 0;
    printStr_in_index = len;
	UART0_C2 |= UART_C2_TIE_MASK;
}

void UART_ReadLine(char* str, int strLen){
    //readStr = str;
    //maxChars = strLen;
    UART0_C2 |= UART_C2_RIE_MASK;
}


//-----------------------------------------------------------------
//  UART0 configuration
//-----------------------------------------------------------------
void InitUARTs(){

    SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; // Make sure clock for PORTA is enabled
    SIM_SCGC4 |= SIM_SCGC4_UART0_MASK; // Enable peripheral clock

	PORTA_PCR1 = PORT_PCR_MUX(2) | PORT_PCR_DSE_MASK;  // RX
	PORTA_PCR2 = PORT_PCR_MUX(2) | PORT_PCR_DSE_MASK;  // TX

	//Select PLL/2 Clock
	SIM_SOPT2 &= ~(3<<26);
	SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

	//We have to feed this function the clock in KHz!
	Uart0_Br_Sbr(CORE_CLOCK/2/1000, SDA_SERIAL_BAUD);
	 //Enable receive interrupts

	UART0_C2 = UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK | UARTLP_C2_RIE_MASK; // Enable Transmitter, Receiver, Receive interrupt
	set_irq_priority(INT_UART0-16,0);
	enable_irq(INT_UART0-16);

}

//--------------------------------------------------------------------
//  UART0 - Selection of BR (Baud Rate) and OSR (Over Sampling Ratio)
//--------------------------------------------------------------------
void Uart0_Br_Sbr(int sysclk, int baud){

    uint8 i;
    uint32 calculated_baud = 0;
    uint32 baud_diff = 0;
    uint32 osr_val = 0;
    uint32 sbr_val, uart0clk;
    uint32 baud_rate;
    uint32 reg_temp = 0;
    uint32 temp = 0;

    SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

    // Disable UART0 before changing registers
    UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);

    // Verify that a valid clock value has been passed to the function
    if ((sysclk > 50000) || (sysclk < 32))
    {
        sysclk = 0;
        reg_temp = SIM_SOPT2;
        reg_temp &= ~SIM_SOPT2_UART0SRC_MASK;
        reg_temp |= SIM_SOPT2_UART0SRC(0);
        SIM_SOPT2 = reg_temp;

			  // Enter infinite loop because the
			  // the desired system clock value is
			  // invalid!!
			  while(1);

    }


    // Initialize baud rate
    baud_rate = baud;

    // Change units to Hz
    uart0clk = sysclk * 1000;
    // Calculate the first baud rate using the lowest OSR value possible.
    i = 4;
    sbr_val = (uint32)(uart0clk/(baud_rate * i));
    calculated_baud = (uart0clk / (i * sbr_val));

    if (calculated_baud > baud_rate)
        baud_diff = calculated_baud - baud_rate;
    else
        baud_diff = baud_rate - calculated_baud;

    osr_val = i;

    // Select the best OSR value
    for (i = 5; i <= 32; i++)
    {
        sbr_val = (uint32)(uart0clk/(baud_rate * i));
        calculated_baud = (uart0clk / (i * sbr_val));

        if (calculated_baud > baud_rate)
            temp = calculated_baud - baud_rate;
        else
            temp = baud_rate - calculated_baud;

        if (temp <= baud_diff)
        {
            baud_diff = temp;
            osr_val = i;
        }
    }

    if (baud_diff < ((baud_rate / 100) * 3))
    {
        // If the OSR is between 4x and 8x then both
        // edge sampling MUST be turned on.
        if ((osr_val >3) && (osr_val < 9))
            UART0_C5|= UART0_C5_BOTHEDGE_MASK;

        // Setup OSR value
        reg_temp = UART0_C4;
        reg_temp &= ~UART0_C4_OSR_MASK;
        reg_temp |= UART0_C4_OSR(osr_val-1);

        // Write reg_temp to C4 register
        UART0_C4 = reg_temp;

        reg_temp = (reg_temp & UART0_C4_OSR_MASK) + 1;
        sbr_val = (uint32)((uart0clk)/(baud_rate * (reg_temp)));

         /* Save off the current value of the uartx_BDH except for the SBR field */
        reg_temp = UART0_BDH & ~(UART0_BDH_SBR(0x1F));

        UART0_BDH = reg_temp |  UART0_BDH_SBR(((sbr_val & 0x1F00) >> 8));
        UART0_BDL = (uint8)(sbr_val & UART0_BDL_SBR_MASK);

        /* Enable receiver and transmitter */
        UART0_C2 |= (UART0_C2_TE_MASK
                    | UART0_C2_RE_MASK );
    }
    else
		{
        // Unacceptable baud rate difference
        // More than 3% difference!!
        // Enter infinite loop!
        while(1);

		}

}
