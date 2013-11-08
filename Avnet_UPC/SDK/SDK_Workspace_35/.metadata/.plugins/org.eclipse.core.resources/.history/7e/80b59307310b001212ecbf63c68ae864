################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/application.c \
../src/bsp.c 

OBJS += \
./src/application.o \
./src/bsp.o 

C_DEPS += \
./src/application.d \
./src/bsp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O3 -I../../../../microblaze_0/include -I../../../../microblaze_0/libsrc/uartlite_v2_00_a/src -c -fmessage-length=0 -I../../uCOS-II_bsp_0/microblaze_0/include -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.00.a -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


