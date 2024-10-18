################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../W5500/W5500.c \
../W5500/W5500_HAL.c \
../W5500/W5500_LL.c \
../W5500/W5500_TCP.c \
../W5500/W5500_UDP.c 

OBJS += \
./W5500/W5500.o \
./W5500/W5500_HAL.o \
./W5500/W5500_LL.o \
./W5500/W5500_TCP.o \
./W5500/W5500_UDP.o 

C_DEPS += \
./W5500/W5500.d \
./W5500/W5500_HAL.d \
./W5500/W5500_LL.d \
./W5500/W5500_TCP.d \
./W5500/W5500_UDP.d 


# Each subdirectory must supply rules for building sources it contributes
W5500/%.o W5500/%.su W5500/%.cyclo: ../W5500/%.c W5500/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VETx -c -I../Inc -I"D:/STM32F407_Firmware/W5500_Driver/GPIO" -I"D:/STM32F407_Firmware/W5500_Driver/SPI" -I"D:/STM32F407_Firmware/W5500_Driver/W5500" -I"D:/STM32F407_Firmware/W5500_Driver/Console" -I"D:/STM32F407_Firmware/W5500_Driver/USART" -I"D:/STM32F407_Firmware/W5500_Driver/Network_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-W5500

clean-W5500:
	-$(RM) ./W5500/W5500.cyclo ./W5500/W5500.d ./W5500/W5500.o ./W5500/W5500.su ./W5500/W5500_HAL.cyclo ./W5500/W5500_HAL.d ./W5500/W5500_HAL.o ./W5500/W5500_HAL.su ./W5500/W5500_LL.cyclo ./W5500/W5500_LL.d ./W5500/W5500_LL.o ./W5500/W5500_LL.su ./W5500/W5500_TCP.cyclo ./W5500/W5500_TCP.d ./W5500/W5500_TCP.o ./W5500/W5500_TCP.su ./W5500/W5500_UDP.cyclo ./W5500/W5500_UDP.d ./W5500/W5500_UDP.o ./W5500/W5500_UDP.su

.PHONY: clean-W5500

