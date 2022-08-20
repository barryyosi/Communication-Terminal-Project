#include "TFC.h"

#include "MKL25Z4.h"

#include "app_FSM_handler.h"

#include "hal_UART.h"

#include <math.h>


#define SDA_SERIAL_BAUD 9600
#define CORE_CLOCK 48000000
#define MAX_STRING 1000
#define MAX_MSG 32

uint8_t string1[31];
char readStr[MAX_STRING] = {
  0
};
char printStr[MAX_MSG] = {
  0
};
int readStr_index = 0;
int writeStrIdx = 0;
int printStr_out_index = 0;

// TODO - validate

//char message[MAX_MSG] = {0};
//char* pMessage;
char receivedByte;
int i = 0; // Test variable
// File transfer testing variable
int testFileTransfer = 0; // File transfer testing variable

void UART0_IRQHandler() {
  char temp;

  if (UART0_S1 & UART_S1_RDRF_MASK) { // RX buffer is full and ready for reading	
    receivedByte = UART0_D;
    if (!readState) {
      tempState = receivedByte - '0';
      readState = 1;
    } else if (readMsgSize != 4) {
      readMsgSize++;
      msgSize += (receivedByte - '0') * pow(10, 4 - readMsgSize);
      memset( & message[0], 0, sizeof(message));
    } else {
      switch (getState()) {

      case chatMode:
        UART_readMessage();
        break;

      case fileTransferMode:
        if (!fileTransferReady || !readFileName) {
          UART_readMessage();
        } else {
        	for (i = 0; i < fileCount; i++){
        		if (!strcmp(fileName,pFiles[i].name)){
        			send_recv_flag = 1;
        			sentFileIndex = i;
        			msgDisplayed = 1;
        			break;
        		}
        	}
        	if(!send_recv_flag){
			  disable_irq(INT_UART0 - 16); // Disable UART0 interrupt
			  enableDMA();
			  msgDisplayed = 1;
        	}
        }
        break;
 	 
      default:
        UART_readMessage();
        break;
      }

    }

   
  }
  if (UART0_S1 & UART_S1_TDRE_MASK) { // TX buffer is empty and ready for sending
    //			UART0_D = printStr[writeStrIdx++];
    //			if ( printStr[writeStrIdx++] == "\0"){                  // TX over?
    //				writeStrIdx = 0;
    //				UART0_C2 &= ~UART_C2_TIE_MASK;
    //			}
  }

}
void UART_readMessage() {
  message[(idx++) % MAX_MSG] = receivedByte;
  if (idx == (msgSize)) {

    if (getState() == fileTransferMode && !fileTransferReady)
      fileTransferReady = 1;
    else if (getState() == fileTransferMode && !readFileName) {
      extractFileSize(msgSize);
      strcpy(fileName, message);
      readFileName = 1;
    }
    else if (getState() == terminalConfigMode && !terminalConfigReady)
    	terminalConfigReady = 1;
    else if (getState() == terminalConfigMode && !readBaudRateReady)
	    readBaudRateReady = 1;
    
    readState = 0;
    readMsgSize = 0;
    msgSize = 0;
    idx = 0;
    msgDisplayed = 0;

  }
}

void UART_receiveFile() {
  disable_irq(INT_UART0 - 16); // Disable UART0 interrupt
  enableDMA();
  // TODO - enable file DMA transfer	
  // Should ignore this case, DMA should handle it
  // TODO - Also static int readFileName = 0;
  testFileTransfer++;

}

void UART_sendFile(int fileIndex) {
  char * nameFrame = (char * ) malloc(strlen(pFiles[fileIndex].name) + 2);
  strcpy(nameFrame, pFiles[fileIndex].name);
  strcat(nameFrame, "$\0");
  uart0_putstr(nameFrame);
  free(nameFrame);

//  char * contentFrame = (char * ) malloc(pFiles[fileIndex] -> size + 2);
  char contentFrame[MAX_FILE_SIZE];
  strcpy(contentFrame, pFiles[fileIndex].content);
  
  contentFrame[pFiles[fileIndex].size] = '$';
  contentFrame[pFiles[fileIndex].size + 1] = '\0';
  
  uart0_putstr(contentFrame);
//  free(contentFrame);
  
  readFileName = 0;
  enable_irq(INT_UART0 - 16); // Enable UART0 interrupt
  readState = 0;
  readMsgSize = 0;
  msgSize = 0;
  idx = 0;
  msgDisplayed = 0;
}

void uart0_putchar(char ch) {
  while (!(UART0_S1 & UART0_S1_TDRE_MASK));
  UART0_D = (uint8_t) ch;
}

void uart0_putstr(const uint8_t * str) {
  while ( * str != '\0') {
    uart0_putchar( * str++);
  }
  uart0_putchar( * str++);
}

void UART_PrintLine(UART_MemMapPtr channel, char * str) {
  volatile unsigned int i;
  while (!(UART_S1_REG(channel) & UART_S1_TDRE_MASK)); /* Wait until space is available in the FIFO */
  for (i = 0; i < idxInMcuMessage; i++) {
    UART_D_REG(channel) = str[i];
  }
  UART_D_REG(channel) = '\0';
  UART0_C2 |= UART_C2_TIE_MASK;
}

void UART_ReadLine(char * str, int strLen) {
  //readStr = str;
  //maxChars = strLen;
  UART0_C2 |= UART_C2_RIE_MASK;
}

//-----------------------------------------------------------------
//  UART0 configuration
//-----------------------------------------------------------------
void InitUARTs() {

  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK; // Make sure clock for PORTA is enabled
  SIM_SCGC4 |= SIM_SCGC4_UART0_MASK; // Enable peripheral clock

  PORTA_PCR1 = PORT_PCR_MUX(2) | PORT_PCR_DSE_MASK; // RX
  PORTA_PCR2 = PORT_PCR_MUX(2) | PORT_PCR_DSE_MASK; // TX

  //Select PLL/2 Clock
  SIM_SOPT2 &= ~(3 << 26);
  SIM_SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
  SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);
  SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;

  //We have to feed this function the clock in KHz!
  Uart0_Br_Sbr(CORE_CLOCK / 2 / 1000, SDA_SERIAL_BAUD);
  //Enable receive interrupts
  //	UART0_C1 |= 0x4;
  UART0_C2 = UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK | UARTLP_C2_RIE_MASK; // Enable Transmitter, Receiver, Receive interrupt
  set_irq_priority(INT_UART0 - 16, 0);
  enable_irq(INT_UART0 - 16);
  fileTransferReady = 0;

}

//--------------------------------------------------------------------
//  UART0 - Selection of BR (Baud Rate) and OSR (Over Sampling Ratio)
//--------------------------------------------------------------------
void Uart0_Br_Sbr(int sysclk, int baud) {

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
  if ((sysclk > 50000) || (sysclk < 32)) {
    sysclk = 0;
    reg_temp = SIM_SOPT2;
    reg_temp &= ~SIM_SOPT2_UART0SRC_MASK;
    reg_temp |= SIM_SOPT2_UART0SRC(0);
    SIM_SOPT2 = reg_temp;

    // Enter infinite loop because the
    // the desired system clock value is
    // invalid!!
    while (1);

  }

  // Initialize baud rate
  baud_rate = baud;

  // Change units to Hz
  uart0clk = sysclk * 1000;
  // Calculate the first baud rate using the lowest OSR value possible.
  i = 4;
  sbr_val = (uint32)(uart0clk / (baud_rate * i));
  calculated_baud = (uart0clk / (i * sbr_val));

  if (calculated_baud > baud_rate)
    baud_diff = calculated_baud - baud_rate;
  else
    baud_diff = baud_rate - calculated_baud;

  osr_val = i;

  // Select the best OSR value
  for (i = 5; i <= 32; i++) {
    sbr_val = (uint32)(uart0clk / (baud_rate * i));
    calculated_baud = (uart0clk / (i * sbr_val));

    if (calculated_baud > baud_rate)
      temp = calculated_baud - baud_rate;
    else
      temp = baud_rate - calculated_baud;

    if (temp <= baud_diff) {
      baud_diff = temp;
      osr_val = i;
    }
  }

  if (baud_diff < ((baud_rate / 100) * 3)) {
    // If the OSR is between 4x and 8x then both
    // edge sampling MUST be turned on.
    if ((osr_val > 3) && (osr_val < 9))
      UART0_C5 |= UART0_C5_BOTHEDGE_MASK;

    // Setup OSR value
    reg_temp = UART0_C4;
    reg_temp &= ~UART0_C4_OSR_MASK;
    reg_temp |= UART0_C4_OSR(osr_val - 1);

    // Write reg_temp to C4 register
    UART0_C4 = reg_temp;

    reg_temp = (reg_temp & UART0_C4_OSR_MASK) + 1;
    sbr_val = (uint32)((uart0clk) / (baud_rate * (reg_temp)));

    /* Save off the current value of the uartx_BDH except for the SBR field */
    reg_temp = UART0_BDH & ~(UART0_BDH_SBR(0x1F));

    UART0_BDH = reg_temp | UART0_BDH_SBR(((sbr_val & 0x1F00) >> 8));
    UART0_BDL = (uint8)(sbr_val & UART0_BDL_SBR_MASK);

    /* Enable receiver and transmitter */
    UART0_C2 |= (UART0_C2_TE_MASK |
      UART0_C2_RE_MASK);
  } else {
    // Unacceptable baud rate difference
    // More than 3% difference!!
    // Enter infinite loop!
    while (1);

  }

}

/********************************************************************/
/*
 * Wait for a character to be received on the specified uart
 *
 * Parameters:
 *  channel      UART channel to read from
 *
 * Return Values:
 *  the received character
 */
char uart_getchar(UART_MemMapPtr channel) {
  /* Wait until character has been received */
  while (!(UART_S1_REG(channel) & UART_S1_RDRF_MASK));

  /* Return the 8-bit data from the receiver */
  return UART_D_REG(channel);
}

/********************************************************************/
/*
 * Wait for space in the uart Tx FIFO and then send a character
 *
 * Parameters:
 *  channel      UART channel to send to
 *  ch			 character to send
 */
void uart_putchar(UART_MemMapPtr channel, char ch) {
  /* Wait until space is available in the FIFO */
  while (!(UART_S1_REG(channel) & UART_S1_TDRE_MASK));

  /* Send the character */
  UART_D_REG(channel) = (uint8) ch;

}
