/*
 *
 * SystemC TLM API Standard Proposal and Examples
 * Copyright Cadence Design Systems Inc 2004
 *
 */

#include "master1.h"

using user_3master::master1;

master1::master1( sc_module_name module_name ) :
  sc_module( module_name ) , 
  initiator_port("iport")
{
  SC_THREAD( run );
}

void master1::run()
{

  // DATA_TYPE d = 1;
  // unsigned int i = 0;

  // cout << " ====================== MASTER1 ======================= " << endl; 
  // // // cout << " =============== This is data WRITING!! =============== " << endl; 
  // // for( i = 0; i < 20; i++ )
  // // {

  //   cout << "Writing Address " << i << " value " << d << endl;
  //   initiator_port.write( i , d );

  // // }

}
