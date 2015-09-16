// file name = sink.h

#include "systemc.h"
// #include "channel.h"

class sink : public sc_module
{

public:
	sc_port< sc_fifo_in_if<char> > in;

	SC_HAS_PROCESS(sink);

	sink(sc_module_name name)
	{
		SC_THREAD(sink_p);
	}

	void sink_p();
	
};
