################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include app/subdir.mk
-include Services/subdir.mk
-include MCAL/UART/subdir.mk
-include MCAL/Timer1/subdir.mk
-include MCAL/Timer0/subdir.mk
-include MCAL/I2C/subdir.mk
-include MCAL/EXTI/subdir.mk
-include MCAL/EEPROM/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/Servo/subdir.mk
-include HAL/RAIN_SENSOR/subdir.mk
-include HAL/PB/subdir.mk
-include HAL/LED/subdir.mk
-include HAL/LCD_ST7920/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/KP/subdir.mk
-include HAL/BLUETOOTH/subdir.mk
-include HAL/7SEG/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
sender3.lss \

FLASH_IMAGE += \
sender3.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: sender3.elf secondary-outputs

# Tool invocations
sender3.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,sender3.map -mmcu=atmega32 -o "sender3.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

sender3.lss: sender3.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S sender3.elf  >"sender3.lss"
	@echo 'Finished building: $@'
	@echo ' '

sender3.hex: sender3.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex sender3.elf  "sender3.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: sender3.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 sender3.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) sender3.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
