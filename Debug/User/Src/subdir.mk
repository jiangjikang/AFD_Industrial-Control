################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/Src/crc16.c \
../User/Src/modbus.c \
../User/Src/relay.c \
../User/Src/valve.c 

OBJS += \
./User/Src/crc16.o \
./User/Src/modbus.o \
./User/Src/relay.o \
./User/Src/valve.o 

C_DEPS += \
./User/Src/crc16.d \
./User/Src/modbus.d \
./User/Src/relay.d \
./User/Src/valve.d 


# Each subdirectory must supply rules for building sources it contributes
User/Src/%.o User/Src/%.su User/Src/%.cyclo: ../User/Src/%.c User/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Files/water_controller/User/Inc" -I"D:/Files/water_controller/User/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-User-2f-Src

clean-User-2f-Src:
	-$(RM) ./User/Src/crc16.cyclo ./User/Src/crc16.d ./User/Src/crc16.o ./User/Src/crc16.su ./User/Src/modbus.cyclo ./User/Src/modbus.d ./User/Src/modbus.o ./User/Src/modbus.su ./User/Src/relay.cyclo ./User/Src/relay.d ./User/Src/relay.o ./User/Src/relay.su ./User/Src/valve.cyclo ./User/Src/valve.d ./User/Src/valve.o ./User/Src/valve.su

.PHONY: clean-User-2f-Src

