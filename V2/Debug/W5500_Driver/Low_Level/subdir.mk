################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../W5500_Driver/Low_Level/W5500_Low_Level.c 

OBJS += \
./W5500_Driver/Low_Level/W5500_Low_Level.o 

C_DEPS += \
./W5500_Driver/Low_Level/W5500_Low_Level.d 


# Each subdirectory must supply rules for building sources it contributes
W5500_Driver/Low_Level/%.o W5500_Driver/Low_Level/%.su W5500_Driver/Low_Level/%.cyclo: ../W5500_Driver/Low_Level/%.c W5500_Driver/Low_Level/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"B:/STM32F407V_Firmware_C_Lang/W5500_Driver/Driver" -I"B:/STM32F407V_Firmware_C_Lang/W5500_Driver/W5500_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-W5500_Driver-2f-Low_Level

clean-W5500_Driver-2f-Low_Level:
	-$(RM) ./W5500_Driver/Low_Level/W5500_Low_Level.cyclo ./W5500_Driver/Low_Level/W5500_Low_Level.d ./W5500_Driver/Low_Level/W5500_Low_Level.o ./W5500_Driver/Low_Level/W5500_Low_Level.su

.PHONY: clean-W5500_Driver-2f-Low_Level

