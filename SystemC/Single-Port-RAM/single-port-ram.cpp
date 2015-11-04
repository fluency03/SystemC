//===========================================
// Function : Asynchronous read write RAM 
// Coder    : Deepak Kumar Tala
// Date     : 18-April-2002
//===========================================
#include "systemc.h"

#define DATA_WIDTH        8 
#define ADDR_WIDTH        8 
#define RAM_DEPTH        1 << ADDR_WIDTH

SC_MODULE (ram_sp_ar_aw) {
  sc_in    <sc_uint<ADDR_WIDTH> > address ;
  sc_in    <bool>                 cs      ;
  sc_in    <bool>                 we      ;
  sc_in    <bool>                 oe      ;
  sc_in    <sc_uint<DATA_WIDTH> > data_in ;
  sc_out   <sc_uint<DATA_WIDTH> > data_out;

  //-----------Internal variables-------------------
  sc_uint <DATA_WIDTH> mem [RAM_DEPTH];

  // Memory Write Block 
  // Write Operation : When we = 1, cs = 1
  void write_mem () {
    if (cs.read() && we.read()) {
      mem[address.read()] = data_in.read();
    }
  }

  // Memory Read Block 
  // Read Operation : When we = 0, oe = 1, cs = 1
  void read_mem () {
    if (cs.read() && !we.read() && oe.read())  {
      data_out.write(mem[address.read()]);
    }
  }

  SC_CTOR(ram_sp_ar_aw) {
    SC_METHOD (read_mem);
      sensitive << address << cs << we << oe;
    SC_METHOD (write_mem);
      sensitive << address << cs << we << data_in;
  }

};


int sc_main(int argc, char* argv[])
{

  ram_sp_ar_aw ram1("ram1");

  sc_start(5000, SC_NS);

  return 0;
}