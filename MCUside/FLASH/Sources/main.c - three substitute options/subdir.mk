################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/main.c - three substitute options/Ex1.c" \
"../Sources/main.c - three substitute options/Ex2.c" \
"../Sources/main.c - three substitute options/Ex3.c" \

C_SRCS += \
../Sources/main.c\ -\ three\ substitute\ options/Ex1.c \
../Sources/main.c\ -\ three\ substitute\ options/Ex2.c \
../Sources/main.c\ -\ three\ substitute\ options/Ex3.c \

OBJS += \
./Sources/main.c\ -\ three\ substitute\ options/Ex1.o \
./Sources/main.c\ -\ three\ substitute\ options/Ex2.o \
./Sources/main.c\ -\ three\ substitute\ options/Ex3.o \

C_DEPS += \
./Sources/main.c\ -\ three\ substitute\ options/Ex1.d \
./Sources/main.c\ -\ three\ substitute\ options/Ex2.d \
./Sources/main.c\ -\ three\ substitute\ options/Ex3.d \

OBJS_QUOTED += \
"./Sources/main.c - three substitute options/Ex1.o" \
"./Sources/main.c - three substitute options/Ex2.o" \
"./Sources/main.c - three substitute options/Ex3.o" \

C_DEPS_QUOTED += \
"./Sources/main.c - three substitute options/Ex1.d" \
"./Sources/main.c - three substitute options/Ex2.d" \
"./Sources/main.c - three substitute options/Ex3.d" \

OBJS_OS_FORMAT += \
./Sources/main.c\ -\ three\ substitute\ options/Ex1.o \
./Sources/main.c\ -\ three\ substitute\ options/Ex2.o \
./Sources/main.c\ -\ three\ substitute\ options/Ex3.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/main.c\ -\ three\ substitute\ options/Ex1.o: ../Sources/main.c\ -\ three\ substitute\ options/Ex1.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.c - three substitute options/Ex1.args" -MMD -MP -MF"Sources/main.c - three substitute options/Ex1.d" -o"Sources/main.c - three substitute options/Ex1.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.c\ -\ three\ substitute\ options/Ex2.o: ../Sources/main.c\ -\ three\ substitute\ options/Ex2.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.c - three substitute options/Ex2.args" -MMD -MP -MF"Sources/main.c - three substitute options/Ex2.d" -o"Sources/main.c - three substitute options/Ex2.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.c\ -\ three\ substitute\ options/Ex3.o: ../Sources/main.c\ -\ three\ substitute\ options/Ex3.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.c - three substitute options/Ex3.args" -MMD -MP -MF"Sources/main.c - three substitute options/Ex3.d" -o"Sources/main.c - three substitute options/Ex3.o"
	@echo 'Finished building: $<'
	@echo ' '


