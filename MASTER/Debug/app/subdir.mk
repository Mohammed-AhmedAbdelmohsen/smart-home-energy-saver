################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/App_Init.c \
../app/Bluetooth_Cmd.c \
../app/Master_Tasks.c \
../app/Slave_Link.c \
../app/TempControl.c \
../app/main.c 

OBJS += \
./app/App_Init.o \
./app/Bluetooth_Cmd.o \
./app/Master_Tasks.o \
./app/Slave_Link.o \
./app/TempControl.o \
./app/main.o 

C_DEPS += \
./app/App_Init.d \
./app/Bluetooth_Cmd.d \
./app/Master_Tasks.d \
./app/Slave_Link.d \
./app/TempControl.d \
./app/main.d 


# Each subdirectory must supply rules for building sources it contributes
app/%.o: ../app/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


