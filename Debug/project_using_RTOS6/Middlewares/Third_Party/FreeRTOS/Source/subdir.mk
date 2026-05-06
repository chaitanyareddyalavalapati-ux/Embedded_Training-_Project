################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/croutine.c \
../project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/event_groups.c \
../project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/list.c \
../project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/queue.c \
../project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.c \
../project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/tasks.c \
../project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/timers.c 

C_DEPS += \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/croutine.d \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/event_groups.d \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/list.d \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/queue.d \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.d \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/tasks.d \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/timers.d 

OBJS += \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/croutine.o \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/event_groups.o \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/list.o \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/queue.o \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.o \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/tasks.o \
./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/timers.o 


# Each subdirectory must supply rules for building sources it contributes
project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/%.o project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/%.su project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/%.cyclo: ../project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/%.c project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../project_using_RTOS6/Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-project_using_RTOS6-2f-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source

clean-project_using_RTOS6-2f-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source:
	-$(RM) ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/croutine.cyclo ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/croutine.d ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/croutine.o ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/croutine.su ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/event_groups.cyclo ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/event_groups.d ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/event_groups.o ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/event_groups.su ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/list.cyclo ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/list.d ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/list.o ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/list.su ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/queue.cyclo ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/queue.d ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/queue.o ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/queue.su ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.cyclo ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.d ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.o ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/stream_buffer.su ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/tasks.cyclo ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/tasks.d ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/tasks.o ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/tasks.su ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/timers.cyclo ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/timers.d ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/timers.o ./project_using_RTOS6/Middlewares/Third_Party/FreeRTOS/Source/timers.su

.PHONY: clean-project_using_RTOS6-2f-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source

