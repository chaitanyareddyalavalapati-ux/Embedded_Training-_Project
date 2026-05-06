################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../project_using_RTOS6/Core/Startup/startup_stm32f407vgtx.s 

S_DEPS += \
./project_using_RTOS6/Core/Startup/startup_stm32f407vgtx.d 

OBJS += \
./project_using_RTOS6/Core/Startup/startup_stm32f407vgtx.o 


# Each subdirectory must supply rules for building sources it contributes
project_using_RTOS6/Core/Startup/%.o: ../project_using_RTOS6/Core/Startup/%.s project_using_RTOS6/Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-project_using_RTOS6-2f-Core-2f-Startup

clean-project_using_RTOS6-2f-Core-2f-Startup:
	-$(RM) ./project_using_RTOS6/Core/Startup/startup_stm32f407vgtx.d ./project_using_RTOS6/Core/Startup/startup_stm32f407vgtx.o

.PHONY: clean-project_using_RTOS6-2f-Core-2f-Startup

