// file name= UART.h

/* 
This module emulate the behavior of th UART
It reads one byte from the bus and it sends it to external world.
*/

#include"systemc.h"

SC_MODULE(UART)
{
	sc_in<char> char_in;
	sc_out<char> char_out;

	void prc_UART();
	
	SC_CTOR(UART)
	{
	SC_METHOD (prc_UART);
	sensitive << char_in;
	}

};
