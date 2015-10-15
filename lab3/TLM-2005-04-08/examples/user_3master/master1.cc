/*
 *
 * SystemC TLM API Standard Proposal and Examples
 * Copyright Cadence Design Systems Inc 2004
 *
 */

#include "master1.h"

using user_3master::master1;

master1::master1( sc_module_name module_name, int select ) :
  sc_module( module_name ) , 
  initiator_port("iport")
{
  if (select == 1){
    SC_THREAD( run1 );
    sensitive << clk.pos();
  }

  if (select == 2){
    SC_THREAD( run2 );
    sensitive << clk.pos();
  }

  if (select == 3){
    SC_THREAD( run3 );
    sensitive << clk.pos();
  }

}

void master1::run1()
{

  DATA_TYPE d = 1;
  unsigned int i = 0;

  for( i = 0; i < 20; i++ )
  {

    cout << " ====================== MASTER1 ======================= " << endl; 
    cout << "Writing Address " << i << " value " << d << endl;
    initiator_port.write( i , d );
    wait();

  }

}

void master1::run2()
{

  DATA_TYPE d = 2;
  unsigned int i = 0;
 
  for( i = 0; i < 20; i++ )
  {

    cout << " ====================== MASTER2 ======================= " << endl;
    cout << "Writing Address " << i << " value " << d << endl;
    initiator_port.write( i , d );
    wait();

  }

}

void master1::run3()
{

  DATA_TYPE d;
  unsigned int i = 0;

  for( i = 0; i < 20; i++ )
  {

    initiator_port.read( i , d );
    cout << " ====================== MASTER3 ======================= " << endl; 
    cout << "Read Address " << i << " got " << d << endl;
    wait();

  }
}
