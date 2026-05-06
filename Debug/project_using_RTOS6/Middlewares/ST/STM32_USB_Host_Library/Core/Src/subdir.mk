################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.c \
../project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c \
../project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c \
../project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.c 

C_DEPS += \
./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.d \
./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.d \
./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.d \
./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.d 

OBJS += \
./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.o \
./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.o \
./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.o \
./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.o 


# Each subdirectory must supply rules for building sources it contributes
project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/%.o project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/%.su project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/%.cyclo: ../project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/%.c project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../project_using_RTOS6/Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-project_using_RTOS6-2f-Middlewares-2f-ST-2f-STM32_USB_Host_Library-2f-Core-2f-Src

clean-project_using_RTOS6-2f-Middlewares-2f-ST-2f-STM32_USB_Host_Library-2f-Core-2f-Src:
	-$(RM) ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.cyclo ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.d ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.o ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.su ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.cyclo ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.d ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.o ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.su ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.cyclo ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.d ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.o ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.su ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.cyclo ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.d ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.o ./project_using_RTOS6/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.su

.PHONY: clean-project_using_RTOS6-2f-Middlewares-2f-ST-2f-STM32_USB_Host_Library-2f-Core-2f-Src

