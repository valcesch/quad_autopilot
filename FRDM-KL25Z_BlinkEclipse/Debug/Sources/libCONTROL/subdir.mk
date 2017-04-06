################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/libCONTROL/control.c 

OBJS += \
./Sources/libCONTROL/control.o 

C_DEPS += \
./Sources/libCONTROL/control.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/libCONTROL/%.o: ../Sources/libCONTROL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-none-eabi-gcc -I"C:\Users\Raphael\workspace\FRDM-KL25Z_BlinkEclipse\Project_Headers" -I"C:\Users\Raphael\workspace\FRDM-KL25Z_BlinkEclipse\Project_Settings\Startup_Code" -I"C:\Users\Raphael\workspace\FRDM-KL25Z_BlinkEclipse\Sources" -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m0 -mabi=aapcs -mthumb -msoft-float -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


