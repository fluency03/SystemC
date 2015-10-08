/*
 *
 * SystemC TLM API Standard Proposal and Examples
 * Copyright Cadence Design Systems Inc 2004
 *
 */

#include "master3.h"

using user_3master::master3;

master3::master3( sc_module_name module_name ) :
  sc_module( module_name ) , 
  initiator_port("iport")
{
  SC_THREAD( run );
}

void master3::run()
{

  // DATA_TYPE d;
  // unsigned int i = 0;

  // cout << " ====================== MASTER3 ======================= " << endl; 
  // // // cout << " =============== This is data READING!! =============== " << endl;
  // // for( i = 0; i < 20; i++ )
  // // {

  //   initiator_port.read( i , d );
  //   cout << "Read Address " << i << " got " << d << endl;

  // // }

}
