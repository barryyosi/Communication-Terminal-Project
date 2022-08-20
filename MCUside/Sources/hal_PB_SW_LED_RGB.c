#include "TFC.h"

#include "hal_PB_SW_LED_RGB.h"

#include "bsp_gpio.h"

#include "MKL25Z4.h"

#include "hal_UART.h"
 //--------------- inits

void initPushButton(uint8_t push_button_id) {
  InitInput(PushButtons[push_button_id]);
  setIRQType(PushButtons[push_button_id], PUSH_BUTTON_DEFAULT_EDGE(push_button_id));
}

void initSwitch(uint8_t switch_id) {
  InitInput(Switches[switch_id]);
  setIRQType(Switches[switch_id], INTERRUPT_ON_EITHER_EDGE);
}

void initLed(uint8_t led_id) {
  initOutput(Leds[led_id]);
}

void initRGBLed() {
  int led_id;
  for (led_id = 0; led_id < RGB_LED_NUM; led_id++) {
    initOutput(RGB_leds[led_id]);
  }
}

//---------------------

void turnOnLed(uint8_t led_id) {
  setOutputData(Leds[led_id], 1);
}
void turnOffLed(uint8_t led_id) {
  setOutputData(Leds[led_id], 0);
}
void toggleLed(uint8_t led_id) {
  togglePin(Leds[led_id]);
}

void toggleRGB() {
  static int RGBstate = 0;
  setOutputData(RGB_leds[0], RGBstate & BIT(0));
  setOutputData(RGB_leds[1], RGBstate & BIT(1));
  setOutputData(RGB_leds[2], RGBstate & BIT(2));
  RGBstate = (RGBstate + 1) % 7;
}

//----------

void enablePortIRQ() {

  enable_irq(INT_PORTA - 16);
  enable_irq(INT_PORTD - 16);
}

DeviceId getIRQSource(PortBase base) {

  if (getIRQFlag(PushButtons[0]) == 1 && PushButtons[0].base == base) {
    clearIRQFlag(PushButtons[0]);
    return PUSH_BUTTON_0;
  }
  if (getIRQFlag(PushButtons[1]) == 1 && PushButtons[1].base == base) {
    clearIRQFlag(PushButtons[1]);
    return PUSH_BUTTON_1;
  }
  if (getIRQFlag(PushButtons[2]) == 1 && PushButtons[2].base == base) {
    clearIRQFlag(PushButtons[2]);
    return PUSH_BUTTON_2;
  }
  if (getIRQFlag(PushButtons[3]) == 1 && PushButtons[3].base == base) {
    clearIRQFlag(PushButtons[3]);
    return PUSH_BUTTON_3;
  }

  if (getIRQFlag(Switches[0]) == 1 && Switches[0].base == base) {
    clearIRQFlag(Switches[0]);
    return SWITCH_0;
  }
  if (getIRQFlag(Switches[1]) == 1 && Switches[1].base == base) {
    clearIRQFlag(Switches[1]);
    return SWITCH_1;
  }
  if (getIRQFlag(Switches[2]) == 1 && Switches[2].base == base) {
    clearIRQFlag(Switches[2]);
    return SWITCH_2;
  }
  if (getIRQFlag(Switches[3]) == 1 && Switches[3].base == base) {
    clearIRQFlag(Switches[3]);
    return SWITCH_3;
  }

  if (getIRQFlag(Keypad_IRQ) == 1 && Keypad_IRQ.base == base) {
    return KEYPAD_IRQ;
  }

  return DEVICE_NOT_FOUND; // the return is only to avoid warning
}

void PORTD_IRQHandler() {

  DeviceId deviceId = getIRQSource(BASE_D);
  handleDevicesInterrupt(deviceId);

}