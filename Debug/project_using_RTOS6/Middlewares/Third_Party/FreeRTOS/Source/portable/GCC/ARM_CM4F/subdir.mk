################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c 

C_DEPS += \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d 

OBJS += \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o 


# Each subdirectory must supply rules for building sources it contributes
project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.o project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.su project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.cyclo: ../project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.c project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../project_using_RTOS6/Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-project_using_RTOS6-2f-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F

clean-project_using_RTOS6-2f-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.cyclo ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.su

.PHONY: clean-project_using_RTOS6-2f-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F

