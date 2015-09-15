// file name = or_gate.h
// block name = DUT

#include "systemc.h"
SC_MODULE(or_gate){

	sc_in<bool> a;
	sc_in<bool> b;
	sc_out<bool> c;

	void pro_or_gate();

	SC_CTOR(or_gate){
		SC_METHOD(pro_or_gate);
		sensitive << a << b;
	}

};

