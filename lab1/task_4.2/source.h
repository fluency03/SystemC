// file name = source.h

#include "systemc.h"
// #include "channel.h"

class source : public sc_module
{

public:
    sc_port< sc_fifo_out_if<char> > out;

    SC_HAS_PROCESS(source);
	
    source(sc_module_name name) : sc_module(name)
    {
       SC_THREAD(source_p);
    }

    void source_p();
};
