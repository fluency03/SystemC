// file name = testbench.h

#include "systemc.h"

// block name = driver
SC_MODULE(driver){

	sc_out<bool> d_a;
	sc_out<bool> d_b;

	void driver_a();
	void driver_b();

	SC_CTOR(driver){
		SC_THREAD(driver_a);
		SC_THREAD(driver_b);
		// SC_METHOD(driver_a);
		// SC_METHOD(driver_b);
	}

};

// block name = monitor
SC_MODULE(monitor){

	sc_in<bool> m_a, m_b;
	sc_in<bool> m_c;

	void pro_monitor();

	SC_CTOR(monitor){
		SC_METHOD(pro_monitor);
		sensitive << m_a << m_b << m_c;
	}

};


