
#ifndef GENERAL_MACROS_H_
#define GENERAL_MACROS_H_

#include "TFC.h"

// our definitions
#define     debounceVal      0.25
#define     NOT_ACTIVE       0


// universal definitions
#define OUTPUT 1
#define INPUT  0

#define true   1
#define false  0


// -------------- arithmetic ---------------- //
#define   SEC_TO_MILLI(x)  (x*1000)
#define   MILLI_TO_SEC(x)  (x/1000.0f)
#define   ITERS_PER_SEC    0x240000
#define   KILO             1000
#define   KILO_BYTE        1024
#define   MEGA_BYTE        (KILO_BYTE*KILO_BYTE)
#define   FREQ_TO_TIME(x)  (1/(float)x)
#define   ABS(x) (((x)>=0)?(x):(-(x)))
#define   POSITIVE_MODULO(value, modulo) ((((value) % (modulo)) + (modulo)) % (modulo))


#define TOLERANCE 0.1
#define IS_TOLERATE(originValue, newValue) (((float)ABS(originValue-newValue)) < TOLERANCE*originValue)

#define TPM_FREQ (24*MEGA_BYTE)

// -------------- bit manicpulation ---------------- //

#define PORT_LOC(x)         ((uint32_t)(1<<x))
#define BIT(x)              (1<<x)
// #define WRITE_BIT(var, bit_num, value) (if(value){var |= BIT(bit_num);} else{var &=~ BIT(bit_num);})
#define WRITE_BIT(var, bit_num, value) ((value)? (var |= BIT(bit_num)) : (var &=~ BIT(bit_num)))
#define GET_BIT_VALUE(var, bit_num) ((var &= BIT(bit_num)) >> bit_num)

#define GET_MASK_VALUE(var, mask, shift) ((var & mask) >> shift);
#define WRITE_MASK(var, mask, shift, value)  (var = (uint32_t)(var&(uint32_t)(~(uint32_t)mask)) | (uint32_t)((uint32_t)value << shift))
typedef uint8_t bit_t; // indicate that the value should be 1 or 0


void convert12BitToChar(double maxValue, int rawValue, char * valueSrting);


void DelayUs(unsigned int cnt);
void DelayMs(unsigned int cnt);

// #define PULL_UP            		IRQ_CONFIG_FALLING_EDGE
// #define PULL_DOWN           	IRQ_CONFIG_RISING_EDGE


typedef enum {
  DISABLE_ROLE        = 0,
  GPIO_ROLE           = 1,
  INPUT_CAPTURE_ROLE  = 3
} PortRole;


typedef enum {
  IRQ_DISABALED                = 0x0,
  DMA_ON_RISING_EDGE           = 0x1,
  DMA_ON_FALLIING_EDGE         = 0x2,
  DMA_ON_EITHER_EDGE           = 0x3,
  INTERRUPT_ON_ZERO            = 0x8,
  INTERRUPT_ON_RISING_EDGE     = 0x9,
  INTERRUPT_ON_FALLIING_EDGE   = 0xA,
  INTERRUPT_ON_EITHER_EDGE     = 0xB,
  INTERRUPT_ON_ONE             = 0xC
} IRQType;


typedef enum{
    BASE_A = 0,
    BASE_B,
    BASE_C,
    BASE_D,
    BASE_E,
    BASE_NUM
} PortBase;

typedef struct
{
    PortBase base;
    uint8_t bit;
}Port;


#endif
