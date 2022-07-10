#include "hal_ADC_DAC.h"
#include "MKL25Z4.h"
#include "bsp_gpio.h"
#include "arm_cm0.h"
#include "hal_LCD.h"
#include "TFC.h"

/******************************************************************************
Function 1. Name	AUTO CAL ROUTINE

Parameters		ADC module pointer points to adc0 or adc1 register map
                         base address.
Returns			Zero indicates success.
Notes         		Calibrates the ADC16. Required to meet specifications
                        after reset and before a conversion is initiated.
******************************************************************************/
void enableADC(){
    ADC0_SC1A = AIEN_ON | POT_ADC_CHANNEL;  //POT channel is SE0 , ADC interrupt is enabled.
}
void disableADC(){
    ADC0_SC1A = AIEN_ON | ADC_SC1_ADCH(31);  //POT channel is SE0 , ADC interrupt is enabled.
}

static uint64_t last_sampleSum = 0;
static uint64_t sampleSum = 0;
static uint32_t sampleTimes = 0;
static char avgString[17];

void ADC0_IRQHandler(){
    int adc_value = ADC0_RA;

    sampleTimes++;
    sampleSum += adc_value;
    if(sampleTimes == 64*1024){
        if(ABS(sampleSum - last_sampleSum) >= (2*2<<16)){
            sampleSum = sampleSum >> 16;
            convert12BitToChar(3.28, sampleSum, avgString);
            lcd_printNewLn(avgString);
            last_sampleSum = sampleSum;
        }
        sampleSum = 0;
        sampleTimes = 0;
    }



}

unsigned char ADC_Calibration(ADC_MemMapPtr adcmap)
{

  unsigned short cal_var;

  ADC_SC2_REG(adcmap) &=  ~ADC_SC2_ADTRG_MASK ; // Enable Software Conversion Trigger for Calibration Process    - ADC0_SC2 = ADC0_SC2 | ADC_SC2_ADTRGW(0);
  ADC_SC3_REG(adcmap) &= ( ~ADC_SC3_ADCO_MASK & ~ADC_SC3_AVGS_MASK ); // set single conversion, clear avgs bitfield for next writing
  ADC_SC3_REG(adcmap) |= ( ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(AVGS_32) );  // Turn averaging ON and set at max value ( 32 )


  ADC_SC3_REG(adcmap) |= ADC_SC3_CAL_MASK ;      // Start CAL
  while ( (ADC_SC1_REG(adcmap,A) & ADC_SC1_COCO_MASK ) == COCO_NOT ); // Wait calibration end

  if ((ADC_SC3_REG(adcmap)& ADC_SC3_CALF_MASK) == CALF_FAIL )
  {
   return(1);    // Check for Calibration fail error and return
  }
  // Calculate plus-side calibration
  cal_var = 0x00;

  cal_var =  ADC_CLP0_REG(adcmap);
  cal_var += ADC_CLP1_REG(adcmap);
  cal_var += ADC_CLP2_REG(adcmap);
  cal_var += ADC_CLP3_REG(adcmap);
  cal_var += ADC_CLP4_REG(adcmap);
  cal_var += ADC_CLPS_REG(adcmap);

  cal_var = cal_var/2;
  cal_var |= 0x8000; // Set MSB

  ADC_PG_REG(adcmap) = ADC_PG_PG(cal_var);


  // Calculate minus-side calibration
  cal_var = 0x00;

  cal_var =  ADC_CLM0_REG(adcmap);
  cal_var += ADC_CLM1_REG(adcmap);
  cal_var += ADC_CLM2_REG(adcmap);
  cal_var += ADC_CLM3_REG(adcmap);
  cal_var += ADC_CLM4_REG(adcmap);
  cal_var += ADC_CLMS_REG(adcmap);

  cal_var = cal_var/2;

  cal_var |= 0x8000; // Set MSB

  ADC_MG_REG(adcmap) = ADC_MG_MG(cal_var);

  ADC_SC3_REG(adcmap) &= ~ADC_SC3_CAL_MASK ; /* Clear CAL bit */

  return(0);
}




/******************************************************************************
Function 2 Name 	ADC_Config_Alt
Parameters		the register values to be set in the adc in a structure
Returns			NONE
Notes         		Configures ADC0 or ADC1 depending on adcmap
                        Prior to calling this function populate the structure
                        elements with the desired ADC configuration.
******************************************************************************/


void ADC_Config_Alt(ADC_MemMapPtr adcmap, tADC_ConfigPtr ADC_CfgPtr)
{
 ADC_CFG1_REG(adcmap) = ADC_CfgPtr->CONFIG1;
 ADC_CFG2_REG(adcmap) = ADC_CfgPtr->CONFIG2;
 ADC_CV1_REG(adcmap)  = ADC_CfgPtr->COMPARE1;
 ADC_CV2_REG(adcmap)  = ADC_CfgPtr->COMPARE2;
 ADC_SC2_REG(adcmap)  = ADC_CfgPtr->STATUS2;
 ADC_SC3_REG(adcmap)  = ADC_CfgPtr->STATUS3;
 //ADC_PGA_REG(adcmap)  = ADC_CfgPtr->PGA;
 ADC_SC1_REG(adcmap,A)= ADC_CfgPtr->STATUS1A;
 ADC_SC1_REG(adcmap,B)= ADC_CfgPtr->STATUS1B;
}


void ADC_Read_Cal(ADC_MemMapPtr adcmap, tADC_Calibration_Blk *blk)
{
  blk->OFS  = ADC_OFS_REG(adcmap);
  blk->PG   = ADC_PG_REG(adcmap);
  blk->MG   = ADC_MG_REG(adcmap);
  blk->CLPD = ADC_CLPD_REG(adcmap);
  blk->CLPS = ADC_CLPS_REG(adcmap);
  blk->CLP4 = ADC_CLP4_REG(adcmap);
  blk->CLP3 = ADC_CLP3_REG(adcmap);
  blk->CLP2 = ADC_CLP2_REG(adcmap);
  blk->CLP1 = ADC_CLP1_REG(adcmap);
  blk->CLP0 = ADC_CLP0_REG(adcmap);
  blk->CLMD = ADC_CLMD_REG(adcmap);
  blk->CLMS = ADC_CLMS_REG(adcmap);
  blk->CLM4 = ADC_CLM4_REG(adcmap);
  blk->CLM3 = ADC_CLM3_REG(adcmap);
  blk->CLM2 = ADC_CLM2_REG(adcmap);
  blk->CLM1 = ADC_CLM1_REG(adcmap);
  blk->CLM0 = ADC_CLM0_REG(adcmap);

}



void InitADC0(){

	tADC_Config Master_Adc0_Config;  // structure declaration (of struct adc_cfg)


    SIM_SCGC6 |= (SIM_SCGC6_ADC0_MASK);

    //Lets calibrate the ADC. 1st setup how the channel will be used.

    disable_irq(INT_ADC0-16);

    Master_Adc0_Config.CONFIG1 = ADLPC_NORMAL 			//No low power mode
								| ADC_CFG1_ADIV(ADIV_4)             //divide input by 4
								| ADLSMP_LONG 			                //long sample time                          - in formula add cycles in ADC_CFG2_ADLSTS
								| ADC_CFG1_MODE(MODE_12)            //single ended 12-bit conversion
								| ADC_CFG1_ADICLK(ADICLK_BUS);      // Bus clock

    Master_Adc0_Config.CONFIG2 = MUXSEL_ADCA        // select the A side of the ADC channel.
								| ADACKEN_DISABLED                  // Ansync clock output disable
								| ADHSC_HISPEED                     // High speed conversion mode               - in formula add 2 cycles
								| ADC_CFG2_ADLSTS(ADLSTS_2);        //Extra long sample Time (20 extra clocks)  - in formula add 2 cycles


    Master_Adc0_Config.COMPARE1 = 00000; // Comparators don't matter for calibration
    Master_Adc0_Config.COMPARE1 = 0xFFFF;

    Master_Adc0_Config.STATUS2  = ADTRG_HW //hardware triggers for calibration
                               | ACFE_DISABLED //disable comparator
                               | ACFGT_GREATER
                               | ACREN_ENABLED
                               | DMAEN_DISABLED //Disable DMA
                               | ADC_SC2_REFSEL(REFSEL_ALT); //Internal Reference

    Master_Adc0_Config.STATUS3 = CAL_OFF  // Calibration begin or off
								| ADCO_SINGLE  // single conversion
    						    | AVGE_ENABLED  // Averaging enabled
								| ADC_SC3_AVGS(AVGS_4); // 4 averaged sampales prior to "interrupting" the MCU  - in formula multi by 4

    Master_Adc0_Config.PGA =     0; // Disable the PGA


    // Configure ADC as it will be used, but because ADC_SC1_ADCH is 31,
    // the ADC will be inactive.  Channel 31 is just disable function.
    // There really is no channel 31.

    Master_Adc0_Config.STATUS1A = AIEN_ON | DIFF_SINGLE | ADC_SC1_ADCH(31); // // ADC interrupts enabled, single channel, disable ADC module


    ADC_Config_Alt(ADC0_BASE_PTR, &Master_Adc0_Config);  // config ADC

    // Calibrate the ADC in the configuration in which it will be used:
     ADC_Calibration(ADC0_BASE_PTR);                    // do the calibration


     Master_Adc0_Config.STATUS2  = ACFE_DISABLED //disable comparator
                                | ACFGT_GREATER
                                | ACREN_ENABLED
                                | DMAEN_DISABLED //Disable DMA
                                | ADC_SC2_REFSEL(REFSEL_ALT); //Internal Reference

     Master_Adc0_Config.STATUS3 = CAL_OFF
     							| ADCO_CONTINUOUS;

     ADC_Config_Alt(ADC0_BASE_PTR, &Master_Adc0_Config);
}



void InitADCs(){

	InitADC0();
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK; //Enable clock to the PIT
	ADC0_CFG2  &= ~ADC_CFG2_MUXSEL_MASK; //Select the A side of the mux (For channel SE0)

	enable_irq(INT_PIT-16);
	enable_irq(INT_ADC0-16);
}

void InitDAC(){
//When the DAC is enabled and the buffer is not enabled,
//the DAC module always converts the data in DAT0 to analog output voltage.
// pin PTE30 is by default (ALT0) configured as DAC0_OUT
	//VDDA reference voltage (Use this option for the best ADC operation).
	SIM_SCGC6 |= SIM_SCGC6_DAC0_MASK; //DAC0 Clock Gate Control
	DAC0_C0 |= DAC_C0_DACEN_MASK + DAC_C0_DACRFS_MASK + DAC_C0_DACTRGSEL_MASK + DAC_C0_LPEN_MASK;

}

