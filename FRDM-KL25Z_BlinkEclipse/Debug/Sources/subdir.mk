################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/CDC1.c \
../Sources/CI2C1.c \
../Sources/CLS1.c \
../Sources/CS1.c \
../Sources/Cpu.c \
../Sources/EInt1.c \
../Sources/EInt2.c \
../Sources/EInt3.c \
../Sources/EInt4.c \
../Sources/EInt5.c \
../Sources/EInt6.c \
../Sources/EInt7.c \
../Sources/Events.c \
../Sources/FC1.c \
../Sources/FRTOS1.c \
../Sources/GPIO1.c \
../Sources/MCUC1.c \
../Sources/PE_LDD.c \
../Sources/PWM1.c \
../Sources/PWM2.c \
../Sources/PWM3.c \
../Sources/PWM4.c \
../Sources/Rx1.c \
../Sources/TMOUT1.c \
../Sources/TU1.c \
../Sources/TU3.c \
../Sources/Tx1.c \
../Sources/USB0.c \
../Sources/USB1.c \
../Sources/UTIL1.c \
../Sources/Vectors.c \
../Sources/WAIT1.c \
../Sources/XF1.c \
../Sources/croutine.c \
../Sources/event_groups.c \
../Sources/heap_1.c \
../Sources/heap_2.c \
../Sources/heap_3.c \
../Sources/heap_4.c \
../Sources/heap_5.c \
../Sources/list.c \
../Sources/main.c \
../Sources/port.c \
../Sources/queue.c \
../Sources/tasks.c \
../Sources/timers.c \
../Sources/usb_cdc.c \
../Sources/usb_cdc_pstn.c \
../Sources/usb_class.c \
../Sources/usb_dci_kinetis.c \
../Sources/usb_descriptor.c \
../Sources/usb_driver.c \
../Sources/usb_framework.c \
../Sources/wdt_kinetis.c 

OBJS += \
./Sources/CDC1.o \
./Sources/CI2C1.o \
./Sources/CLS1.o \
./Sources/CS1.o \
./Sources/Cpu.o \
./Sources/EInt1.o \
./Sources/EInt2.o \
./Sources/EInt3.o \
./Sources/EInt4.o \
./Sources/EInt5.o \
./Sources/EInt6.o \
./Sources/EInt7.o \
./Sources/Events.o \
./Sources/FC1.o \
./Sources/FRTOS1.o \
./Sources/GPIO1.o \
./Sources/MCUC1.o \
./Sources/PE_LDD.o \
./Sources/PWM1.o \
./Sources/PWM2.o \
./Sources/PWM3.o \
./Sources/PWM4.o \
./Sources/Rx1.o \
./Sources/TMOUT1.o \
./Sources/TU1.o \
./Sources/TU3.o \
./Sources/Tx1.o \
./Sources/USB0.o \
./Sources/USB1.o \
./Sources/UTIL1.o \
./Sources/Vectors.o \
./Sources/WAIT1.o \
./Sources/XF1.o \
./Sources/croutine.o \
./Sources/event_groups.o \
./Sources/heap_1.o \
./Sources/heap_2.o \
./Sources/heap_3.o \
./Sources/heap_4.o \
./Sources/heap_5.o \
./Sources/list.o \
./Sources/main.o \
./Sources/port.o \
./Sources/queue.o \
./Sources/tasks.o \
./Sources/timers.o \
./Sources/usb_cdc.o \
./Sources/usb_cdc_pstn.o \
./Sources/usb_class.o \
./Sources/usb_dci_kinetis.o \
./Sources/usb_descriptor.o \
./Sources/usb_driver.o \
./Sources/usb_framework.o \
./Sources/wdt_kinetis.o 

C_DEPS += \
./Sources/CDC1.d \
./Sources/CI2C1.d \
./Sources/CLS1.d \
./Sources/CS1.d \
./Sources/Cpu.d \
./Sources/EInt1.d \
./Sources/EInt2.d \
./Sources/EInt3.d \
./Sources/EInt4.d \
./Sources/EInt5.d \
./Sources/EInt6.d \
./Sources/EInt7.d \
./Sources/Events.d \
./Sources/FC1.d \
./Sources/FRTOS1.d \
./Sources/GPIO1.d \
./Sources/MCUC1.d \
./Sources/PE_LDD.d \
./Sources/PWM1.d \
./Sources/PWM2.d \
./Sources/PWM3.d \
./Sources/PWM4.d \
./Sources/Rx1.d \
./Sources/TMOUT1.d \
./Sources/TU1.d \
./Sources/TU3.d \
./Sources/Tx1.d \
./Sources/USB0.d \
./Sources/USB1.d \
./Sources/UTIL1.d \
./Sources/Vectors.d \
./Sources/WAIT1.d \
./Sources/XF1.d \
./Sources/croutine.d \
./Sources/event_groups.d \
./Sources/heap_1.d \
./Sources/heap_2.d \
./Sources/heap_3.d \
./Sources/heap_4.d \
./Sources/heap_5.d \
./Sources/list.d \
./Sources/main.d \
./Sources/port.d \
./Sources/queue.d \
./Sources/tasks.d \
./Sources/timers.d \
./Sources/usb_cdc.d \
./Sources/usb_cdc_pstn.d \
./Sources/usb_class.d \
./Sources/usb_dci_kinetis.d \
./Sources/usb_descriptor.d \
./Sources/usb_driver.d \
./Sources/usb_framework.d \
./Sources/wdt_kinetis.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-none-eabi-gcc -I"C:\Users\Raphael\workspace\FRDM-KL25Z_BlinkEclipse\Project_Headers" -I"C:\Users\Raphael\workspace\FRDM-KL25Z_BlinkEclipse\Project_Settings\Startup_Code" -I"C:\Users\Raphael\workspace\FRDM-KL25Z_BlinkEclipse\Sources" -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m0 -mabi=aapcs -mthumb -msoft-float -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


