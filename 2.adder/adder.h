// adder.h
#include "systemc.h"

//SC_MODULE (myDesign) {
	//ports, processes, internal data, etc.
	//SC_CTOR (myDesign) {
		//body of constructor;
		//process declaration, sensitivities, etc.
	// }
// };

SC_MODULE(Adder){
	sc_in<int> a;
	sc_in<int> b;
	sc_out<int> c;

	void compute();

	SC_CTOR(Adder){
		SC_METHOD(compute);
		sensitive << a << b;
	}

};

