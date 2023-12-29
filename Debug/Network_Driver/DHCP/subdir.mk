################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Network_Driver/DHCP/DHCP.c 

OBJS += \
./Network_Driver/DHCP/DHCP.o 

C_DEPS += \
./Network_Driver/DHCP/DHCP.d 


# Each subdirectory must supply rules for building sources it contributes
Network_Driver/DHCP/%.o Network_Driver/DHCP/%.su Network_Driver/DHCP/%.cyclo: ../Network_Driver/DHCP/%.c Network_Driver/DHCP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VETx -c -I../Inc -I"D:/STM32F407_Firmware/W5500_Driver/GPIO" -I"D:/STM32F407_Firmware/W5500_Driver/SPI" -I"D:/STM32F407_Firmware/W5500_Driver/W5500" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Network_Driver-2f-DHCP

clean-Network_Driver-2f-DHCP:
	-$(RM) ./Network_Driver/DHCP/DHCP.cyclo ./Network_Driver/DHCP/DHCP.d ./Network_Driver/DHCP/DHCP.o ./Network_Driver/DHCP/DHCP.su

.PHONY: clean-Network_Driver-2f-DHCP

