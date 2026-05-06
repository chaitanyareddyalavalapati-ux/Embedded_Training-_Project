################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../project_using_RTOS6/USB_HOST/Target/usbh_conf.c \
../project_using_RTOS6/USB_HOST/Target/usbh_platform.c 

C_DEPS += \
./project_using_RTOS6/USB_HOST/Target/usbh_conf.d \
./project_using_RTOS6/USB_HOST/Target/usbh_platform.d 

OBJS += \
./project_using_RTOS6/USB_HOST/Target/usbh_conf.o \
./project_using_RTOS6/USB_HOST/Target/usbh_platform.o 


# Each subdirectory must supply rules for building sources it contributes
project_using_RTOS6/USB_HOST/Target/%.o project_using_RTOS6/USB_HOST/Target/%.su project_using_RTOS6/USB_HOST/Target/%.cyclo: ../project_using_RTOS6/USB_HOST/Target/%.c project_using_RTOS6/USB_HOST/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../project_using_RTOS6/Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-project_using_RTOS6-2f-USB_HOST-2f-Target

clean-project_using_RTOS6-2f-USB_HOST-2f-Target:
	-$(RM) ./project_using_RTOS6/USB_HOST/Target/usbh_conf.cyclo ./project_using_RTOS6/USB_HOST/Target/usbh_conf.d ./project_using_RTOS6/USB_HOST/Target/usbh_conf.o ./project_using_RTOS6/USB_HOST/Target/usbh_conf.su ./project_using_RTOS6/USB_HOST/Target/usbh_platform.cyclo ./project_using_RTOS6/USB_HOST/Target/usbh_platform.d ./project_using_RTOS6/USB_HOST/Target/usbh_platform.o ./project_using_RTOS6/USB_HOST/Target/usbh_platform.su

.PHONY: clean-project_using_RTOS6-2f-USB_HOST-2f-Target

