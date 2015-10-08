/*
 *
 * SystemC TLM API Standard Proposal and Examples
 * Copyright Cadence Design Systems Inc 2004
 *
 */

#include "master2.h"

using user_3master::master2;

master2::master2( sc_module_name module_name ) :
  sc_module( module_name ) , 
  initiator_port("iport")
{
  SC_THREAD( run );
}

void master2::run()
{

  // DATA_TYPE d = 2;
  // unsigned int i = 0;

  // cout << " ====================== MASTER2 ======================= " << endl; 
  // // // cout << " =============== This is data WRITING!! =============== " << endl; 
  // // for( i = 0; i < 20; i++ )
  // // {

  //   cout << "Writing Address " << i << " value " << d << endl;
  //   initiator_port.write( i , d );

  // // }

}
