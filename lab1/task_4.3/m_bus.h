// file name= m_bus.h

#include"systemc.h"

SC_MODULE(m_bus)
{
	sc_in<char> char_in1;
	sc_in<char> char_in2;
	sc_in<bool> selector;
	sc_out<char> char_out;

	void prc_m_bus();

	SC_CTOR(m_bus)
	{
	SC_METHOD (prc_m_bus);
	sensitive << char_in1 << char_in2 << selector;
	}

};
