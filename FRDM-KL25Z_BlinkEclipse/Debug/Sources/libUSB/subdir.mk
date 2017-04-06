################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/libUSB/an_packet_protocol.c \
../Sources/libUSB/an_packets.c \
../Sources/libUSB/com.c \
../Sources/libUSB/crc.c \
../Sources/libUSB/usbdrive.c 

OBJS += \
./Sources/libUSB/an_packet_protocol.o \
./Sources/libUSB/an_packets.o \
./Sources/libUSB/com.o \
./Sources/libUSB/crc.o \
./Sources/libUSB/usbdrive.o 

C_DEPS += \
./Sources/libUSB/an_packet_protocol.d \
./Sources/libUSB/an_packets.d \
./Sources/libUSB/com.d \
./Sources/libUSB/crc.d \
./Sources/libUSB/usbdrive.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/libUSB/%.o: ../Sources/libUSB/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-none-eabi-gcc -I"C:\Users\Raphael\workspace\FRDM-KL25Z_BlinkEclipse\Project_Headers" -I"C:\Users\Raphael\workspace\FRDM-KL25Z_BlinkEclipse\Project_Settings\Startup_Code" -I"C:\Users\Raphael\workspace\FRDM-KL25Z_BlinkEclipse\Sources" -O0 -g3 -Wall -c -fmessage-length=0 -mcpu=cortex-m0 -mabi=aapcs -mthumb -msoft-float -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


