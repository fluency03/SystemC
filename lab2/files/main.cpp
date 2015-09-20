// file name = main.cpp

#include "systemc.h"
#include "ram.h"
// #include "testbench.h"


int sc_main(int argc, char *argv[])
{

	ram ram1("ram1", 32, false);

    sc_trace_file *wf = sc_create_vcd_trace_file("ram_wave");
    sc_trace(wf, ram1.address, "address");
    sc_trace(wf, ram1.data, "data");
    sc_trace(wf, ram1.CE, "CE");
    sc_trace(wf, ram1.WE, "WE");

	sc_signal<bool> WE, CE;
	sc_signal<int> address, data;

	ram1.CE(CE);
	ram1.WE(WE);
	ram1.address(address);
	ram1.data(data);

	CE  	= 0;
    data    = 0;
    address = 0;
    WE      = 0;
    sc_start(0, SC_NS);
 
    WE      = 1;
    address = 0x10;
    data	= 0x11;
    CE  	= 1;
    sc_start(5, SC_NS);
 
    CE  	= 0;
    sc_start(5, SC_NS);
 
    address	= 0x12;
    data	= 0x10;
    CE  	= 1;
    sc_start(5, SC_NS);
 
    address = 0x8;
    data 	= 0x01;
    sc_start(5, SC_NS);
 
    WE      = 0;
    address = 0x10;
    sc_start(5, SC_NS);
 
    address = 0x1;
    sc_start(5, SC_NS);
 
    address = 0x3;
    sc_start(5, SC_NS);
 
    CE  	= 0;
    sc_start(1, SC_NS);


	sc_start(100, SC_NS);

	return 0;

}


