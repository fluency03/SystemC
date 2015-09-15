// file name = source.h

#include"systemc.h"
#include"channel.h"
class source : public sc_module
{
   public:
     sc_port<w_if> out;

    SC_HAS_PROCESS(source);
	
    source(sc_module_name name) : sc_module(name)
     {
       
     }

     void source_p();
};
