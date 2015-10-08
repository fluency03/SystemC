/*
 *
 * SystemC TLM API Standard Proposal and Examples
 * Copyright Cadence Design Systems Inc 2004
 *
 */

#include "master_new.h"

using user_switch::master_new;

master_new::master_new( sc_module_name module_name ) :
  sc_module( module_name ) , 
  initiator_port("iport")
{

  unsigned int i;
  for( i = 0; i < 5; i++ )
    SC_THREAD( run );

}

void master_new::run()
{

  DATA_TYPE d;
  const unsigned int addr[] = {11,15,12,3,33,35,21,18,55,41};
  unsigned int i, random, sum=0;

  cout << " =============== This is data WRITING!! =============== " << endl; 
  for( i = 0; i < 10; i++ )
  {

    random = rand() % 20 +1;
    cout << "Writing Address " << addr[i] << " value " << random << endl;
    initiator_port.write( addr[i] , random );

  }

  cout << " =============== This is data READING!! =============== " << endl;
  for( i = 0; i < 10; i++ )
  {

    initiator_port.read( addr[i] , d );
    cout << "Read Address " << addr[i] << " got " << d << endl;
    sum += d;

  }

  cout << " =============== This is AVERAGE value!! =============== " << endl;
  cout << "The average value: " << ((float)sum/10) << endl;

}
