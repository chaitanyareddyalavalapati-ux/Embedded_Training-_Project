################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../project_using_RTOS6/USB_HOST/App/usb_host.c 

C_DEPS += \
./project_using_RTOS6/USB_HOST/App/usb_host.d 

OBJS += \
./project_using_RTOS6/USB_HOST/App/usb_host.o 


# Each subdirectory must supply rules for building sources it contributes
project_using_RTOS6/USB_HOST/App/%.o project_using_RTOS6/USB_HOST/App/%.su project_using_RTOS6/USB_HOST/App/%.cyclo: ../project_using_RTOS6/USB_HOST/App/%.c project_using_RTOS6/USB_HOST/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../project_using_RTOS6/Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-project_using_RTOS6-2f-USB_HOST-2f-App

clean-project_using_RTOS6-2f-USB_HOST-2f-App:
	-$(RM) ./project_using_RTOS6/USB_HOST/App/usb_host.cyclo ./project_using_RTOS6/USB_HOST/App/usb_host.d ./project_using_RTOS6/USB_HOST/App/usb_host.o ./project_using_RTOS6/USB_HOST/App/usb_host.su

.PHONY: clean-project_using_RTOS6-2f-USB_HOST-2f-App

