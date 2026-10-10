################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/App_Init.c \
../app/App_State.c \
../app/Gate.c \
../app/RoomCount.c \
../app/Slave_Commands.c \
../app/Slave_Tasks.c \
../app/main.c 

OBJS += \
./app/App_Init.o \
./app/App_State.o \
./app/Gate.o \
./app/RoomCount.o \
./app/Slave_Commands.o \
./app/Slave_Tasks.o \
./app/main.o 

C_DEPS += \
./app/App_Init.d \
./app/App_State.d \
./app/Gate.d \
./app/RoomCount.d \
./app/Slave_Commands.d \
./app/Slave_Tasks.d \
./app/main.d 


# Each subdirectory must supply rules for building sources it contributes
app/%.o: ../app/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


