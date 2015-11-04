################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../example_4_1/main.cc 

CC_DEPS += \
./example_4_1/main.d 

OBJS += \
./example_4_1/main.o 


# Each subdirectory must supply rules for building sources it contributes
example_4_1/%.o: ../example_4_1/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/systemc-2.3.1/include -I/home/cliu/workspace/TLM-2005-04-08/tlm -I/home/cliu/workspace/tlm/examples/basic_protocol -I/home/cliu/workspace/tlm/examples/user" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


