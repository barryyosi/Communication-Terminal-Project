#include "app_FSM_handler.h"

#include "BoardSupport.h"

#include "MKL25Z4.h"

#include "hal_UART.h"

#include "hal_ADC_DAC.h"

#include "hal_LCD.h"

#include "hal_timers.h"

#include "app_FSM_handler.h"


FSMstate sysState = sleepMode;

void handleDevicesInterrupt(DeviceId deviceId) {
  char keyPressed;
  char messagePrefix[] = "MCU:";
  int messageSize;
  switch (deviceId) {
  case KEYPAD_IRQ:
    if (getState() == chatMode) {
      if (mcuTyping != 1) {
        lcd_printNewLn(messagePrefix);
        mcuTyping = 1;
        idxInMcuMessage = 0;
      }
      keyPressed = keypad_scan(); // Scanning the keypad & saving the pressed key
      clearIRQFlag(Keypad_IRQ);
      if (keyPressed != 'z') { // Avoiding undefined char.
        lcd_putchar2(keyPressed);
        pitEnable();
        // TODO check if PIT counter is reset to init value on enable/disable
        //      on every key pressed reset the PIT counter
        currentMessageChar = keyPressed;

      }

    }
    break;

  case PUSH_BUTTON_0:
    switch (getState()) {
    case (chatMode): {
      mcuMessage[idxInMcuMessage - 1] = currentMessageChar;
      mcuMessage[idxInMcuMessage] = '$';

      uart0_putstr(mcuMessage);
      memset( & mcuMessage[0], 0, sizeof(mcuMessage));
      lcd_clear();
      mcuTyping = 0;
    }
    break;

    case (fileTransferMode): {
      if (fileCount == 1) {
        char firstFileName[MAX_MSG];
        strcpy(pFiles[0].name, firstFileName);
        lcd_printNewLn(firstFileName);

      } else if (fileCount >= 2)
        filesScrollMenu();
    }
    break;

    default:
      break;
    }
    break;

  case PUSH_BUTTON_1:
    switch (getState()) {
    case fileTransferMode:
      lcd_printFile(currentPointedFileIndex);
    }
    break;

  case PUSH_BUTTON_2:
    switch (getState()) {
    case fileTransferMode:
      UART_sendFile(currentPointedFileIndex);
    }
    break;
  default:
    break;

  }
  DelayMs(100);
}

void setState(FSMstate argState) {
  sysState = argState;
}

FSMstate getState() {
  return sysState;
}

void updateState(FSMstate argState) {
  if (getState() != argState)
    exitState(getState());
  setState(argState);
  enterState(argState);
}

void enterState(FSMstate state) {
  switch (state) {
  case sleepMode: {}
  break;

  case chatMode: {}
  break;

  case fileTransferMode: {

  }
  break;

  case terminalConfigMode: {}
  break;
  }
}

void exitState(FSMstate state) {
  lcd_clear();
  switch (state) {
  case sleepMode: {}
  break;

  case chatMode: {}
  break;

  case fileTransferMode: {
    fileTransferReady = 0;
  }
  break;

  case terminalConfigMode: {
    terminalConfigReady = 0;
  }
  break;

  }
}