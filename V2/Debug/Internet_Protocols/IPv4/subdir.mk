################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Internet_Protocols/IPv4/IPv4.c 

OBJS += \
./Internet_Protocols/IPv4/IPv4.o 

C_DEPS += \
./Internet_Protocols/IPv4/IPv4.d 


# Each subdirectory must supply rules for building sources it contributes
Internet_Protocols/IPv4/%.o Internet_Protocols/IPv4/%.su Internet_Protocols/IPv4/%.cyclo: ../Internet_Protocols/IPv4/%.c Internet_Protocols/IPv4/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/W5500_Driver/Driver" -I"B:/STM32F407V_Firmware_C_Lang/W5500_Driver/W5500_Driver" -I"B:/STM32F407V_Firmware_C_Lang/W5500_Driver/Internet_Protocols" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Internet_Protocols-2f-IPv4

clean-Internet_Protocols-2f-IPv4:
	-$(RM) ./Internet_Protocols/IPv4/IPv4.cyclo ./Internet_Protocols/IPv4/IPv4.d ./Internet_Protocols/IPv4/IPv4.o ./Internet_Protocols/IPv4/IPv4.su

.PHONY: clean-Internet_Protocols-2f-IPv4

