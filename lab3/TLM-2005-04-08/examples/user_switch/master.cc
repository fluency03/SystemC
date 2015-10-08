/*
 *
 * SystemC TLM API Standard Proposal and Examples
 * Copyright Cadence Design Systems Inc 2004
 *
 */

#include "master.h"

using user_switch::master;

master::master( sc_module_name module_name ) :
  sc_module( module_name ) , 
  initiator_port("iport")
{
  SC_THREAD( run );
}

void master::run()
{

  DATA_TYPE d;

  cout << " =============== This is data WRITING!! =============== " << endl; 

  for( ADDRESS_TYPE a = 0; a <= 100; a++ )
  {

    cout << "Writing Address " << a << " value " << a + 50 << endl;
    initiator_port.write( a , a + 200 );

  }

  cout << " =============== This is data READING!! =============== " << endl;

  for( ADDRESS_TYPE a = 0; a <= 100; a++ )
  {

    initiator_port.read( a , d );
    cout << "Read Address " << a << " got " << d << endl;

  }
}
