// monitor.h
#include "systemc.h"

SC_MODULE(Monitor){
	sc_in<bool> clk;
	sc_in<int> a;
	sc_in<int> b;
	sc_in<int> c;

	void printout();

	SC_CTOR (Monitor) {
		SC_THREAD(printout);
		sensitive << clk.pos();
	}

};
