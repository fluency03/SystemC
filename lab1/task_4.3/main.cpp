// file name = main.cpp

#include "UART.h"
#include "arbiter.h"
#include "change_case.h"
#include "filter.h"
#include "m_bus.h"
#include "testbench.h"
#include "systemc.h"

// position binding
SC_MODULE(Top)
{

	sc_signal<char> t2ch, ch2bus, t2fil, fil2bus, bus2uart, uart2t, data; // module connections
	sc_signal<bool> sel2bus;
	sc_clock		clk;

	change_case 	M1;
	filter 			M2;
	arbiter			M3;
	m_bus			M4;
	UART			M5;
	driver			T1;
	monitor			T2;

	SC_CTOR(Top):M1("M1"), M2("M2"), M3("M3"), M4("M4"), M5("M5"), T1("T1"), T2("T2")
	{

		M1.char_in(data);
		M1.char_out(ch2bus);

		M2.char_in(data);
		M2.char_out(fil2bus);

		M3.clk(clk);
		M3.sel(sel2bus);

		M4.char_in1(ch2bus);
		M4.char_in2(fil2bus);
		M4.selector(sel2bus);
		M4.char_out(bus2uart);

		M5.char_in(bus2uart);
		M5.char_out(uart2t);

		T1.d_char(data);
		// T1.d_char(t2fil);

		T2.m_char(uart2t);

	}

};


int sc_main(int argc, char *argv[])
{

	Top top("top");

	sc_start(1000, SC_NS);

	return 0;

}






