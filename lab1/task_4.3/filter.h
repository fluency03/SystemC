// file name= filter.h

#include"systemc.h"

SC_MODULE(filter)
{
	sc_in<char> char_in;
	sc_out<char> char_out;

	void prc_filter();

	SC_CTOR(filter)
	{
	SC_METHOD (prc_filter);
	sensitive << char_in;
	}

};

