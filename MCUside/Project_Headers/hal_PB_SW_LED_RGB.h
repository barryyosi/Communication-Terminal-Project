#ifndef EXTENDED_BOARD_DEVICES_H_
#define EXTENDED_BOARD_DEVICES_H_


#include "TFC.h"

#define PUSH_BUTTON_DEFAULT_EDGE(push_button_id) ((push_button_id==0 || push_button_id==1)?(INTERRUPT_ON_FALLIING_EDGE):(INTERRUPT_ON_RISING_EDGE))

 typedef enum {
     DEVICE_NOT_FOUND = 0,
     PUSH_BUTTON_0,
     PUSH_BUTTON_1,
     PUSH_BUTTON_2,
     PUSH_BUTTON_3,
     SWITCH_0,
     SWITCH_1,
     SWITCH_2,
     SWITCH_3,
     PWM_IN,
     PWM_OUT,
     KEYPAD_IRQ
 } DeviceId;

typedef enum {
    ADC0 = 0,
    ADC1,
    TPM0,
    TPM1,
    TPM2,
    PIT,
    DMA0,
    DMA1,
    DMA2,
    DMA3,
    UART0,
    UART1
} InnerModuleId;



void initPushButton(uint8_t push_button_id);
void initSwitch(uint8_t switch_id);
void initLed(uint8_t led_id);
void initRGBLed();
void toggleRGB();


void turnOnLed(uint8_t led_id);
void turnOffLed(uint8_t led_id);
void toggleLed(uint8_t led_id);
//void PORTD_IRQHandler();
DeviceId getIRQSource(PortBase base);



#endif
