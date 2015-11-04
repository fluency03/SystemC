################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../example_3_3/main.cc \
../example_3_3/mem_fifo_slave.cc 

CC_DEPS += \
./example_3_3/main.d \
./example_3_3/mem_fifo_slave.d 

OBJS += \
./example_3_3/main.o \
./example_3_3/mem_fifo_slave.o 


# Each subdirectory must supply rules for building sources it contributes
example_3_3/%.o: ../example_3_3/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/systemc-2.3.1/include -I/home/cliu/workspace/TLM-2005-04-08/tlm -I/home/cliu/workspace/tlm/examples/basic_protocol -I/home/cliu/workspace/tlm/examples/user" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


