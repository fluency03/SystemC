################################################################################

################################################################################
TLM = ../../tlm
UTILS = ../../utils
PROTOCOL = ../basic_protocol
USER = ../user

GXX = gcc
GXX = g++
TARGET_ARCH = linux64
SYSTEMC_HOME = /usr/local/systemc-2.3.1/

DEPEND = -MM

FLAGS= -g -O3 -Wall -DVERBOSE_GLOBAL -Wno-deprecated -DSC_INCLUDE_DYNAMIC_PROCESSES

## Include directories
INCDIR = -I$(SYSTEMC_HOME)/include -I$(TLM) -I$(UTILS) -I$(PROTOCOL) -I$(USER) -I./

## Library directories
LIBDIR = -L$(SYSTEMC_HOME)/lib-$(TARGET_ARCH)

## SystemC static library
LIB_SC = -lsystemc 

LIBS = $(LIBDIR) $(LIB_SC)  

CFLAGS = $(FLAGS) $(INCDIR) 

## Example .cc files
SRCS = $(wildcard $(USER)/*.cc ./*.cc)
## OBJS = $(subst ./,,$(SRCS:%.cc=%.o))
OBJS = $(SRCS:%.cc=%.o)

all:    Make.dep TLMrun

.c.o:
	$(GX) $(CFLAGS) -c $<
.cc.o:
	$(GXX) $(CFLAGS) -c $< -o $@

TLMrun: $(OBJS)
	$(GXX) -o TLMrun $(OBJS) $(LIBS)

depend:
	$(GXX) $(DEPEND) $(CFLAGS) $(SRCS) > Make.dep	

Make.dep:
	if [ ! -r Make.dep ] ;  then $(GXX) $(DEPEND) $(CFLAGS) $(SRCS) $(TLMSRCS) > Make.dep;fi;

clean:
	\rm -f *.o *.dep TLMrun* *~ #* $(USER)/*.o

include Make.dep


