//top.h
#include "systemc.h"
#include "stimulus.h"
#include "adder.h"
#include "monitor.h"


SC_MODULE (Top) {
	sc_signal<int> siga, sigb, sigc;
	sc_clock testclk;

	Stimulus stim;
	Adder dut;
	Monitor mon;

	SC_CTOR(Top):testclk("testclk"), stim("stim"), dut("dut"), mon("mon") 
	{
		stim.a(siga);
		stim.b(sigb);
		stim.clk(testclk);

		dut.a(siga);
		dut.b(sigb);
		dut.c(sigc);
		//dut(siga, sigb, sigc);

		mon.a(siga);
		mon.b(sigb);
		mon.c(sigc);
		mon.clk(testclk);
	}

};