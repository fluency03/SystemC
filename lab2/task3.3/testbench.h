// file name = testbench.h

#include "systemc.h"

SC_MODULE (driver)
{
	sc_out<int> d; // data generator

	void prc_drive();


	SC_CTOR(driver)
	{
		SC_THREAD (prc_drive); 
	}
};

SC_MODULE (monitor)
{
	sc_in<int> m;

	void prc_monitor();

	SC_CTOR(monitor)
	{
		SC_METHOD(prc_monitor);
		sensitive << m; 
	}
};

