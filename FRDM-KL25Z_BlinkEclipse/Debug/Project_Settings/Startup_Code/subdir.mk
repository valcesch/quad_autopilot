################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../Project_Settings/Startup_Code/kinetis_sysinit.o \
../Project_Settings/Startup_Code/startup.o 

S_UPPER_SRCS += \
../Project_Settings/Startup_Code/startup.S 

OBJS += \
./Project_Settings/Startup_Code/startup.o 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Assembler'
	arm-none-eabi-as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


