################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/libMOTDRIVE/optoe300.c 

OBJS += \
./Sources/libMOTDRIVE/optoe300.o 

C_DEPS += \
./Sources/libMOTDRIVE/optoe300.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/libMOTDRIVE/%.o: ../Sources/libMOTDRIVE/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-none-eabi-gcc -I"C:\Users\Raphael\workspace\FRDM-KL25Z_BlinkEclipse\Project_Headers" -I"C:\Users\Raphael\workspace\FRDM-KL25Z_BlinkEclipse\Project_Settings\Startup_Code" -I"C:\Users\Raphael\workspace\FRDM-KL25Z_BlinkEclipse\Sources" -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m0 -mabi=aapcs -mthumb -msoft-float -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


