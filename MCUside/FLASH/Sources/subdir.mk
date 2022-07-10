################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/BoardSupport.c" \
"../Sources/api.c" \
"../Sources/api_general_macros.c" \
"../Sources/api_lcd.c" \
"../Sources/app_FSM_handler.c" \
"../Sources/arm_cm0.c" \
"../Sources/bsp_connection_map.c" \
"../Sources/bsp_gpio.c" \
"../Sources/hal_ADC_DAC.c" \
"../Sources/hal_LCD.c" \
"../Sources/hal_PB_SW_LED_RGB.c" \
"../Sources/hal_UART.c" \
"../Sources/hal_timers.c" \
"../Sources/main.c" \
"../Sources/mcg.c" \
"../Sources/sa_mtb.c" \

C_SRCS += \
../Sources/BoardSupport.c \
../Sources/api.c \
../Sources/api_general_macros.c \
../Sources/api_lcd.c \
../Sources/app_FSM_handler.c \
../Sources/arm_cm0.c \
../Sources/bsp_connection_map.c \
../Sources/bsp_gpio.c \
../Sources/hal_ADC_DAC.c \
../Sources/hal_LCD.c \
../Sources/hal_PB_SW_LED_RGB.c \
../Sources/hal_UART.c \
../Sources/hal_timers.c \
../Sources/main.c \
../Sources/mcg.c \
../Sources/sa_mtb.c \

OBJS += \
./Sources/BoardSupport.o \
./Sources/api.o \
./Sources/api_general_macros.o \
./Sources/api_lcd.o \
./Sources/app_FSM_handler.o \
./Sources/arm_cm0.o \
./Sources/bsp_connection_map.o \
./Sources/bsp_gpio.o \
./Sources/hal_ADC_DAC.o \
./Sources/hal_LCD.o \
./Sources/hal_PB_SW_LED_RGB.o \
./Sources/hal_UART.o \
./Sources/hal_timers.o \
./Sources/main.o \
./Sources/mcg.o \
./Sources/sa_mtb.o \

C_DEPS += \
./Sources/BoardSupport.d \
./Sources/api.d \
./Sources/api_general_macros.d \
./Sources/api_lcd.d \
./Sources/app_FSM_handler.d \
./Sources/arm_cm0.d \
./Sources/bsp_connection_map.d \
./Sources/bsp_gpio.d \
./Sources/hal_ADC_DAC.d \
./Sources/hal_LCD.d \
./Sources/hal_PB_SW_LED_RGB.d \
./Sources/hal_UART.d \
./Sources/hal_timers.d \
./Sources/main.d \
./Sources/mcg.d \
./Sources/sa_mtb.d \

OBJS_QUOTED += \
"./Sources/BoardSupport.o" \
"./Sources/api.o" \
"./Sources/api_general_macros.o" \
"./Sources/api_lcd.o" \
"./Sources/app_FSM_handler.o" \
"./Sources/arm_cm0.o" \
"./Sources/bsp_connection_map.o" \
"./Sources/bsp_gpio.o" \
"./Sources/hal_ADC_DAC.o" \
"./Sources/hal_LCD.o" \
"./Sources/hal_PB_SW_LED_RGB.o" \
"./Sources/hal_UART.o" \
"./Sources/hal_timers.o" \
"./Sources/main.o" \
"./Sources/mcg.o" \
"./Sources/sa_mtb.o" \

C_DEPS_QUOTED += \
"./Sources/BoardSupport.d" \
"./Sources/api.d" \
"./Sources/api_general_macros.d" \
"./Sources/api_lcd.d" \
"./Sources/app_FSM_handler.d" \
"./Sources/arm_cm0.d" \
"./Sources/bsp_connection_map.d" \
"./Sources/bsp_gpio.d" \
"./Sources/hal_ADC_DAC.d" \
"./Sources/hal_LCD.d" \
"./Sources/hal_PB_SW_LED_RGB.d" \
"./Sources/hal_UART.d" \
"./Sources/hal_timers.d" \
"./Sources/main.d" \
"./Sources/mcg.d" \
"./Sources/sa_mtb.d" \

OBJS_OS_FORMAT += \
./Sources/BoardSupport.o \
./Sources/api.o \
./Sources/api_general_macros.o \
./Sources/api_lcd.o \
./Sources/app_FSM_handler.o \
./Sources/arm_cm0.o \
./Sources/bsp_connection_map.o \
./Sources/bsp_gpio.o \
./Sources/hal_ADC_DAC.o \
./Sources/hal_LCD.o \
./Sources/hal_PB_SW_LED_RGB.o \
./Sources/hal_UART.o \
./Sources/hal_timers.o \
./Sources/main.o \
./Sources/mcg.o \
./Sources/sa_mtb.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/BoardSupport.o: ../Sources/BoardSupport.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/BoardSupport.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/BoardSupport.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/api.o: ../Sources/api.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/api.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/api.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/api_general_macros.o: ../Sources/api_general_macros.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/api_general_macros.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/api_general_macros.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/api_lcd.o: ../Sources/api_lcd.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/api_lcd.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/api_lcd.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/app_FSM_handler.o: ../Sources/app_FSM_handler.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/app_FSM_handler.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/app_FSM_handler.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/arm_cm0.o: ../Sources/arm_cm0.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/arm_cm0.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/arm_cm0.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/bsp_connection_map.o: ../Sources/bsp_connection_map.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/bsp_connection_map.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/bsp_connection_map.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/bsp_gpio.o: ../Sources/bsp_gpio.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/bsp_gpio.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/bsp_gpio.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hal_ADC_DAC.o: ../Sources/hal_ADC_DAC.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/hal_ADC_DAC.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/hal_ADC_DAC.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hal_LCD.o: ../Sources/hal_LCD.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/hal_LCD.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/hal_LCD.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hal_PB_SW_LED_RGB.o: ../Sources/hal_PB_SW_LED_RGB.c
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/hal_PB_SW_LED_RGB.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/hal_PB_SW_LED_RGB.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hal_UART.o: ../Sources/hal_UART.c
	@echo 'Building file: $<'
	@echo 'Executing target #12 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/hal_UART.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/hal_UART.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/hal_timers.o: ../Sources/hal_timers.c
	@echo 'Building file: $<'
	@echo 'Executing target #13 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/hal_timers.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/hal_timers.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/mcg.o: ../Sources/mcg.c
	@echo 'Building file: $<'
	@echo 'Executing target #15 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/mcg.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/mcg.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #16 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '


