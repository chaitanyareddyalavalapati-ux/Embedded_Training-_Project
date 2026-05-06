################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../project_using_RTOS6/Core/Src/lcd.cpp \
../project_using_RTOS6/Core/Src/main.cpp 

C_SRCS += \
../project_using_RTOS6/Core/Src/freertos.c \
../project_using_RTOS6/Core/Src/main.c \
../project_using_RTOS6/Core/Src/stm32f4xx_hal_msp.c \
../project_using_RTOS6/Core/Src/stm32f4xx_hal_timebase_tim.c \
../project_using_RTOS6/Core/Src/stm32f4xx_it.c \
../project_using_RTOS6/Core/Src/syscalls.c \
../project_using_RTOS6/Core/Src/sysmem.c \
../project_using_RTOS6/Core/Src/system_stm32f4xx.c 

C_DEPS += \
./project_using_RTOS6/Core/Src/freertos.d \
./project_using_RTOS6/Core/Src/main.d \
./project_using_RTOS6/Core/Src/stm32f4xx_hal_msp.d \
./project_using_RTOS6/Core/Src/stm32f4xx_hal_timebase_tim.d \
./project_using_RTOS6/Core/Src/stm32f4xx_it.d \
./project_using_RTOS6/Core/Src/syscalls.d \
./project_using_RTOS6/Core/Src/sysmem.d \
./project_using_RTOS6/Core/Src/system_stm32f4xx.d 

OBJS += \
./project_using_RTOS6/Core/Src/freertos.o \
./project_using_RTOS6/Core/Src/lcd.o \
./project_using_RTOS6/Core/Src/main.o \
./project_using_RTOS6/Core/Src/stm32f4xx_hal_msp.o \
./project_using_RTOS6/Core/Src/stm32f4xx_hal_timebase_tim.o \
./project_using_RTOS6/Core/Src/stm32f4xx_it.o \
./project_using_RTOS6/Core/Src/syscalls.o \
./project_using_RTOS6/Core/Src/sysmem.o \
./project_using_RTOS6/Core/Src/system_stm32f4xx.o 

CPP_DEPS += \
./project_using_RTOS6/Core/Src/lcd.d \
./project_using_RTOS6/Core/Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
project_using_RTOS6/Core/Src/%.o project_using_RTOS6/Core/Src/%.su project_using_RTOS6/Core/Src/%.cyclo: ../project_using_RTOS6/Core/Src/%.c project_using_RTOS6/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../project_using_RTOS6/Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
project_using_RTOS6/Core/Src/%.o project_using_RTOS6/Core/Src/%.su project_using_RTOS6/Core/Src/%.cyclo: ../project_using_RTOS6/Core/Src/%.cpp project_using_RTOS6/Core/Src/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../project_using_RTOS6/Core/Inc -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-project_using_RTOS6-2f-Core-2f-Src

clean-project_using_RTOS6-2f-Core-2f-Src:
	-$(RM) ./project_using_RTOS6/Core/Src/freertos.cyclo ./project_using_RTOS6/Core/Src/freertos.d ./project_using_RTOS6/Core/Src/freertos.o ./project_using_RTOS6/Core/Src/freertos.su ./project_using_RTOS6/Core/Src/lcd.cyclo ./project_using_RTOS6/Core/Src/lcd.d ./project_using_RTOS6/Core/Src/lcd.o ./project_using_RTOS6/Core/Src/lcd.su ./project_using_RTOS6/Core/Src/main.cyclo ./project_using_RTOS6/Core/Src/main.d ./project_using_RTOS6/Core/Src/main.o ./project_using_RTOS6/Core/Src/main.su ./project_using_RTOS6/Core/Src/stm32f4xx_hal_msp.cyclo ./project_using_RTOS6/Core/Src/stm32f4xx_hal_msp.d ./project_using_RTOS6/Core/Src/stm32f4xx_hal_msp.o ./project_using_RTOS6/Core/Src/stm32f4xx_hal_msp.su ./project_using_RTOS6/Core/Src/stm32f4xx_hal_timebase_tim.cyclo ./project_using_RTOS6/Core/Src/stm32f4xx_hal_timebase_tim.d ./project_using_RTOS6/Core/Src/stm32f4xx_hal_timebase_tim.o ./project_using_RTOS6/Core/Src/stm32f4xx_hal_timebase_tim.su ./project_using_RTOS6/Core/Src/stm32f4xx_it.cyclo ./project_using_RTOS6/Core/Src/stm32f4xx_it.d ./project_using_RTOS6/Core/Src/stm32f4xx_it.o ./project_using_RTOS6/Core/Src/stm32f4xx_it.su ./project_using_RTOS6/Core/Src/syscalls.cyclo ./project_using_RTOS6/Core/Src/syscalls.d ./project_using_RTOS6/Core/Src/syscalls.o ./project_using_RTOS6/Core/Src/syscalls.su ./project_using_RTOS6/Core/Src/sysmem.cyclo ./project_using_RTOS6/Core/Src/sysmem.d ./project_using_RTOS6/Core/Src/sysmem.o ./project_using_RTOS6/Core/Src/sysmem.su ./project_using_RTOS6/Core/Src/system_stm32f4xx.cyclo ./project_using_RTOS6/Core/Src/system_stm32f4xx.d ./project_using_RTOS6/Core/Src/system_stm32f4xx.o ./project_using_RTOS6/Core/Src/system_stm32f4xx.su

.PHONY: clean-project_using_RTOS6-2f-Core-2f-Src

