#include "app.h"

void receiveFile(char* fName){
    
    pFile file;
    file.Name = fName;
    
    char fileSize[4];
    int j;
    for (j = 0; j < 4; j++)
        fileSize[j] = strlen(fName) - 4 + j;
    
    file.Size = atoi(fileSize);

    // Allocating first place in files DS.
    int i;
    if(fileCount){
        for (i = fileCount - 1; i > 0; i--){
            if(i == FILES_LIMIT - 1)
                continue;
            pFiles[i+1] = pFiles[i];
        }
    }
    pFiles[0] = &file;
    fileCount++;

    DMA_DAR0 = tempFile;                        // Destination - place file in a temporary location, before moving it to it's corresponding pFile instance.
    DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(file.Size);  // Config DMA transfer length.
    DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK; 	// Enable DMA 
    UART0_C5 |= UART0_C5_RDMAE_MASK;          	// Enable DMA request for UART0 receiver 
}
