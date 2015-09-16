// file name = arbiter.h

#include "systemc.h"

SC_MODULE(arbiter)
{
	sc_in<bool> clk;
	sc_out<bool> sel;

	void selection();

	SC_CTOR(arbiter)
	{
		SC_THREAD(selection);
		sensitive << clk.pos();
	}

};


