# Makefile for compiling multiple systemc.cpp files
SYSTEMC_HOME = /usr/local/systemc-2.3.1/
TARGET_ARCH = linux64

SYSTEMC_INC_DIR = $(SYSTEMC_HOME)/include
SYSTEMC_LIB_DIR = $(SYSTEMC_HOME)/lib-$(TARGET_ARCH)

GXX = g++

SRCS = main.cpp UART.cpp arbiter.cpp change_case.cpp filter.cpp m_bus.cpp testbench.cpp 

OUT = run

all: 
	$(GXX) $(SRCS) -I$(SYSTEMC_INC_DIR) -L$(SYSTEMC_LIB_DIR) -lsystemc -o $(OUT)