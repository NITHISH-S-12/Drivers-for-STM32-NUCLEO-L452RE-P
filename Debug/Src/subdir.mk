################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/008spi_cmd_handling.c 

OBJS += \
./Src/008spi_cmd_handling.o 

C_DEPS += \
./Src/008spi_cmd_handling.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DNUCLEO_L452RE_P -DSTM32L452RETxP -DSTM32L4 -DSTM32 -c -I../Inc -I"/home/ubuntu/stm32l452re-p/Drivers-for-STM32-NUCLEO-L452RE-P/drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/008spi_cmd_handling.cyclo ./Src/008spi_cmd_handling.d ./Src/008spi_cmd_handling.o ./Src/008spi_cmd_handling.su

.PHONY: clean-Src

