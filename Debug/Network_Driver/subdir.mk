################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Network_Driver/DHCP.c 

OBJS += \
./Network_Driver/DHCP.o 

C_DEPS += \
./Network_Driver/DHCP.d 


# Each subdirectory must supply rules for building sources it contributes
Network_Driver/%.o Network_Driver/%.su Network_Driver/%.cyclo: ../Network_Driver/%.c Network_Driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VETx -c -I../Inc -I"D:/STM32F407_Firmware/W5500_Driver/GPIO" -I"D:/STM32F407_Firmware/W5500_Driver/SPI" -I"D:/STM32F407_Firmware/W5500_Driver/W5500" -I"D:/STM32F407_Firmware/W5500_Driver/Console" -I"D:/STM32F407_Firmware/W5500_Driver/USART" -I"D:/STM32F407_Firmware/W5500_Driver/Network_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Network_Driver

clean-Network_Driver:
	-$(RM) ./Network_Driver/DHCP.cyclo ./Network_Driver/DHCP.d ./Network_Driver/DHCP.o ./Network_Driver/DHCP.su

.PHONY: clean-Network_Driver

