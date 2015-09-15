// file name = testbench.cpp

#include "testbench.h"

// black name = driver
// two processes generating stimulus for OR gate
void driver::driver_a(){

	d_a.write( (bool)false );
	wait(5, SC_NS);

	d_a.write( (bool)true );
	wait(5, SC_NS);

	d_a.write( (bool)0 );
	wait(5, SC_NS);

	d_a.write( (bool)1 ); 
	wait(5, SC_NS);

}

void driver::driver_b(){

	d_b.write( (bool)0 );
	wait(10, SC_NS);

	d_b.write( (bool)1 ); 
	wait(5, SC_NS);

}


// block name = monitor

void monitor::pro_monitor(){

	cout << "AT time " << sc_time_stamp() << ", input is : ";
	cout << m_a << " , " << m_b << " output is : " << m_c << endl;

}


