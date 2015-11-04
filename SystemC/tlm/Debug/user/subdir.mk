################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../user/master.cc \
../user/mem_slave.cc \
../user/switch_master.cc 

CC_DEPS += \
./user/master.d \
./user/mem_slave.d \
./user/switch_master.d 

OBJS += \
./user/master.o \
./user/mem_slave.o \
./user/switch_master.o 


# Each subdirectory must supply rules for building sources it contributes
user/%.o: ../user/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/systemc-2.3.1/include -I/home/cliu/workspace/TLM-2005-04-08/tlm -I/home/cliu/workspace/tlm/examples/basic_protocol -I/home/cliu/workspace/tlm/examples/user" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


