#include	"TFC.h"

void convert12BitToChar(double maxValue, int rawValue, char * valueSrting) {
  float value = maxValue * rawValue / (float) 0xFFF;
  int beforePoint = (int) value;
  int afterPoint = ((int)(1000 * value)) % 1000;
  sprintf(valueSrting, "Vavg: %2d.%03d[v]", beforePoint, afterPoint);
}

void DelayUs(unsigned int cnt) {

  volatile unsigned int i;
  for (i = cnt * 2; i > 0; i--) asm("nop"); // tha command asm("nop") takes raphly 1usec

}

void DelayMs(unsigned int cnt) {

  volatile unsigned int i;
  for (i = cnt; i > 0; i--) DelayUs(1000); // tha command asm("nop") takes raphly 1usec

}