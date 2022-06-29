################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Free_RTOS/croutine.c \
../Free_RTOS/heap_1.c \
../Free_RTOS/list.c \
../Free_RTOS/port.c \
../Free_RTOS/queue.c \
../Free_RTOS/tasks.c \
../Free_RTOS/timers.c 

C_DEPS += \
./Free_RTOS/croutine.d \
./Free_RTOS/heap_1.d \
./Free_RTOS/list.d \
./Free_RTOS/port.d \
./Free_RTOS/queue.d \
./Free_RTOS/tasks.d \
./Free_RTOS/timers.d 

OBJS += \
./Free_RTOS/croutine.o \
./Free_RTOS/heap_1.o \
./Free_RTOS/list.o \
./Free_RTOS/port.o \
./Free_RTOS/queue.o \
./Free_RTOS/tasks.o \
./Free_RTOS/timers.o 


# Each subdirectory must supply rules for building sources it contributes
Free_RTOS/%.o: ../Free_RTOS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


