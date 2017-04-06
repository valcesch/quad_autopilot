################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Sources/libUSB/subdir.mk
-include Sources/libSENSVECT/subdir.mk
-include Sources/libSENSDRIVE/subdir.mk
-include Sources/libRECDRIVER/subdir.mk
-include Sources/libMOTDRIVE/subdir.mk
-include Sources/libCONTROL/subdir.mk
-include Sources/libADCS/subdir.mk
-include Sources/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: FRDM-KL25Z_BlinkEclipse.elf

# Tool invocations
FRDM-KL25Z_BlinkEclipse.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	arm-none-eabi-gcc -nostartfiles -mthumb -mcpu=cortex-m0 -TC:/Users/Raphael/workspace/FRDM-KL25Z_BlinkEclipse/Project_Settings/Linker_Files/MKL25Z128_flash.ld -o "FRDM-KL25Z_BlinkEclipse.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) FRDM-KL25Z_BlinkEclipse.elf
	-@echo ' '

post-build:
	-@echo 'Generate S19 File'
	-arm-none-eabi-objcopy -O srec C:/Users/Raphael/workspace/FRDM-KL25Z_BlinkEclipse/Debug/FRDM-KL25Z_BlinkEclipse.elf FRDM-KL25Z_BlinkEclipse.s19
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
