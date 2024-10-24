################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Internet_Protocols/DHCP/DHCP.c 

OBJS += \
./Internet_Protocols/DHCP/DHCP.o 

C_DEPS += \
./Internet_Protocols/DHCP/DHCP.d 


# Each subdirectory must supply rules for building sources it contributes
Internet_Protocols/DHCP/%.o Internet_Protocols/DHCP/%.su Internet_Protocols/DHCP/%.cyclo: ../Internet_Protocols/DHCP/%.c Internet_Protocols/DHCP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/W5500_Driver/Driver" -I"B:/STM32F407V_Firmware_C_Lang/W5500_Driver/W5500_Driver" -I"B:/STM32F407V_Firmware_C_Lang/W5500_Driver/Internet_Protocols" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Internet_Protocols-2f-DHCP

clean-Internet_Protocols-2f-DHCP:
	-$(RM) ./Internet_Protocols/DHCP/DHCP.cyclo ./Internet_Protocols/DHCP/DHCP.d ./Internet_Protocols/DHCP/DHCP.o ./Internet_Protocols/DHCP/DHCP.su

.PHONY: clean-Internet_Protocols-2f-DHCP

