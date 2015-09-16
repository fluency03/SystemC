// main.cpp

#include "source.h"
#include "channel.h"
#include "sink.h"
#include "systemc.h"

class top : public sc_module
{

public:
	hw_fifo_wrapper <char> fifo_inst;
	source source1;
	sink sink1;
	sc_clock clk;


	top(sc_module_name name, unsigned size)
		: sc_module(name),
		  fifo_inst("FIFO1", size),
		  source1("source1"),
		  sink1("sink1"),
		  clk("c1", 1, SC_NS)
	{
		source1.out(fifo_inst);
		sink1.in(fifo_inst);
		fifo_inst.clk(clk);
	}

};


int sc_main(int argc, char *argv[])
{

	unsigned size = 30;

	top top1("Top1", size);

	sc_start(1000, SC_NS);

	cout << endl << endl;

	return 0;

}



