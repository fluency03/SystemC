//===========================================
// Function : Asynchronous read write RAM
// Coder    : Deepak Kumar Tala
// Date     : 18-April-2002
//===========================================
// #ifndef RAM_DP_AR_AW
// #define RAM_DP_AR_AW
#include "systemc.h"

#define DATA_WIDTH        8 
#define ADDR_WIDTH        8 
#define RAM_DEPTH         1 << ADDR_WIDTH

SC_MODULE (ram_dp_ar_aw) {
  sc_in    <sc_uint<ADDR_WIDTH> > address_0;
  sc_in    <bool> cs_0 ;
  sc_in    <bool> we_0 ;
  sc_in    <bool> oe_0  ;
  sc_in    <sc_uint<ADDR_WIDTH> > address_1;
  sc_in    <bool> cs_1 ;
  sc_in    <bool> we_1 ;
  sc_in    <bool> oe_1  ;
  sc_inout_rv <DATA_WIDTH> data_0;
  sc_inout_rv <DATA_WIDTH> data_1;

  //-----------Internal variables-------------------
  sc_uint <DATA_WIDTH> mem [RAM_DEPTH];

  //-----------Methods------------------------------
  void  READ_0 ();
  void  READ_1 ();
  void  WRITE_0 ();
  void  WRITE_1 ();

  //-----------Constructor--------------------------
  SC_CTOR(ram_dp_ar_aw) {
    SC_METHOD (READ_0);
      sensitive << address_0 << cs_0 << we_0 << oe_0;
    SC_METHOD (READ_1);
      sensitive << address_1 << cs_1 << we_1 << oe_1;
    SC_METHOD (WRITE_0);
      sensitive << address_0 << cs_0 << we_0 << data_0;
    SC_METHOD (WRITE_1);
      sensitive << address_1 << cs_1 << we_1 << data_1;
  }
};
// #endif


// #include "ram_dp_ar_aw.h"

void  ram_dp_ar_aw::READ_0 () {
  if (cs_0.read() && oe_0.read() && !we_0.read()) {
    data_0 = mem[address_0.read()];
  }
}

void  ram_dp_ar_aw::READ_1 () {
  if (cs_1.read() && oe_1.read() && !we_1.read()) {
    data_1 = mem[address_1.read()];
  }
}

void  ram_dp_ar_aw::WRITE_0 () {
  if (cs_0.read() && we_0.read()) {
    mem[address_0.read()] = data_0.read();
  } 
}

void  ram_dp_ar_aw::WRITE_1 () {
  if (cs_1.read() && we_1.read()) {
    mem[address_1.read()] = data_1.read();
  } 
}



int sc_main(int argc, char* argv[])
{

  ram_dp_ar_aw ram1("ram1");

  sc_start(5000, SC_NS);

  return 0;
}



