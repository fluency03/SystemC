//stimulus.h
#include "systemc.h"

SC_MODULE (Stimulus) {
	sc_in<bool> clk;
	sc_out<int> a;
	sc_out<int> b;

	void generate();

	SC_CTOR (Stimulus) {
		SC_THREAD(generate);
		sensitive << clk.pos();
	}
};
