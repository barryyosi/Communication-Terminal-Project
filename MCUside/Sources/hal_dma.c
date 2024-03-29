#include "hal_dma.h"

char tempFile3[MAX_FILE_SIZE];

char getTempFile(int idx) {
  return tempFile3[idx];
}
void initDMA() {

  // Enable clocks
  SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
  SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

  // Disable DMA Mux channels
  DMAMUX0_CHCFG0 = 0x00;
  DMAMUX0_CHCFG1 = 0x00;

  // Configure DMA0
  DMA_DSR_BCR0 = DMA_DSR_BCR_DONE_MASK;
  DMA_SAR0 = (uint32_t) & UART0_D;

  DMA_DCR0 |= (DMA_DCR_EINT_MASK | // Enable interrupt
    DMA_DCR_ERQ_MASK | // Enable peripheral request
    DMA_DCR_CS_MASK | // Cycle Steal
    DMA_DCR_SSIZE(1) | // Set source size to 8 bits = 1 byte
    DMA_DCR_DINC_MASK | // Set increments to destination address
    DMA_DCR_DMOD(8) | // Destination address modulo of 2K Bytes
    DMA_DCR_DSIZE(1)); // Set destination size of 8 bits = 1 byte

  //Config DMA Mux for UART0  receiver operation, Enable DMA channel and source
  DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_SOURCE(2); // Set UART0 receiver as source

  // Configure DMA1
  DMA_DSR_BCR1 = DMA_DSR_BCR_DONE_MASK;
  DMA_DAR1 = (uint32_t) & UART0_D;

  DMA_DCR1 |= (DMA_DCR_EINT_MASK | // Enable interrupt
    DMA_DCR_ERQ_MASK | // Enable peripheral request
    DMA_DCR_CS_MASK |
    DMA_DCR_SSIZE(1) | // Set source size to 8 bits = 1 byte
    DMA_DCR_SINC_MASK | // Set increments to source address
    DMA_DCR_SMOD(8) | // Destination address modulo of 2K Bytes
    DMA_DCR_DSIZE(1) | // Set destination size of 8 bits = 1 byte
    DMA_DCR_AA_MASK); // Enable auto alignment

  DMAMUX0_CHCFG1 |= DMAMUX_CHCFG_SOURCE(3);

  // Enable interrupt

}

void enableDMA() {
  
  tempFile2 = (char*)malloc(currentFileSize + 1);
  if (tempFile2 == NULL)	
	  lcd_printNewLn("MALLOC ERROR");
  DMA_DAR0 = tempFile2; //destination
  	
  DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(currentFileSize); // number of bytes to transfer
  DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK; // Enable DMA channel
  UART0_C5 |= UART0_C5_RDMAE_MASK; // Enable DMA request for UART0 receiver; }		// Enable interrupt

  enable_irq(INT_DMA0 - 16);
  //	enable_irq(INT_DMA1 - 16);
  DMA_DCR0 |= DMA_DCR_START_MASK;
}
/*
 * Handles DMA0 interrupt
 * Resets the BCR register and clears the DONE flag
 * */
void DMA0_IRQHandler(void) {
  //disable_irq(INT_DMA0 - 16);
  // tempFile3[0] = receivedByte; // Last received byte should be the first byte of the file.
  // tempFile3[currentFileSize] = '\0';
  receiveFile(fileName);
  dmaIrqFlag = 1;
  DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK; // Clear Done Flag
  DMAMUX0_CHCFG0 &= ~DMAMUX_CHCFG_ENBL_MASK; // Disable DMA Channel 0
  UART0_C5 &= ~UART0_C5_RDMAE_MASK; // Disabling DMA using UART
  enable_irq(INT_UART0 - 16); // Enable UART0 interrupt
  int j;
  for (j = 1000000; j > 0; j--); // Delay
}

void DMA1_IRQHandler(void) {
  DMA_DSR_BCR1 |= DMA_DSR_BCR_DONE_MASK; // Clear Done Flag
  DMAMUX0_CHCFG1 &= ~DMAMUX_CHCFG_ENBL_MASK; // Disable DMA Channel 1
  UART0_C5 &= ~UART0_C5_TDMAE_MASK; // Disabling DMA using UART
  enable_irq(INT_UART0 - 16); // Enable UART0 interrupt
  int j;
  for (j = 1000000; j > 0; j--); // Delay
}
