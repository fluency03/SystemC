/*
 *
 * SystemC TLM API Standard Proposal and Examples
 * Copyright Cadence Design Systems Inc 2004
 *
 */

#include "master1.h"

using user_4node::master1;

master1::master1( sc_module_name module_name, int select ) :
  sc_module( module_name ) , 
  initiator_port("iport") ,
  target_port("tport") ,
  count(0), offer(0)
{

  target_port( *this );
  memory = new ADDRESS_TYPE[ 64 ];

  if (select == 0){
    SC_THREAD( run0 );
    sensitive << clk.pos();
  }

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

void master1::run0()
{

  DATA_TYPE d = 1;

  FILE *fp = fopen("node0.txt","r"); // open file 
  if(!fp) {
    cout << "error. cannot find ram initial file." << endl;
  }

  int ad, num;
  while (fscanf(fp, "%i %x", &ad, &num) != EOF) {
    d = uint8_t(num);
    cout << name() << " offers data: " << d << " to " << "node" << ad << endl;
    initiator_port.write( ad , d );
    offer++;
    wait();
  }

}

void master1::run1()
{

  DATA_TYPE d = 1;

  FILE *fp = fopen("node1.txt","r"); // open file 
  if(!fp) {
    cout << "error. cannot find ram initial file." << endl;
  }

  int ad, num;
  while (fscanf(fp, "%i %x", &ad, &num) != EOF) {
    d = uint8_t(num);
    cout << name() << " offers data: " << d << " to " << "node" << ad << endl;
    initiator_port.write( ad , d );
    offer++;
    wait();
  }

}

void master1::run2()
{

  DATA_TYPE d = 1;

  FILE *fp = fopen("node2.txt","r"); // open file 
  if(!fp) {
    cout << "error. cannot find ram initial file." << endl;
  }

  int ad, num;
  while (fscanf(fp, "%i %x", &ad, &num) != EOF) {
    d = uint8_t(num);
    cout << name() << " offers data: " << d << " to " << "node" << ad << endl;
    initiator_port.write( ad , d );
    offer++;
    wait();
  }

}

void master1::run3()
{

  DATA_TYPE d = 1;

  FILE *fp = fopen("node3.txt","r"); // open file 
  if(!fp) {
    cout << "error. cannot find ram initial file." << endl;
  }

  int ad, num;
  while (fscanf(fp, "%i %x", &ad, &num) != EOF) {
    d = uint8_t(num);
    cout << name() << " offers data: " << d << " to " << "node" << ad << endl;
    initiator_port.write( ad , d );
    offer++;
    wait();
  }

}

basic_status master1::write( const ADDRESS_TYPE &a , const DATA_TYPE &d )
{

  cout << name() << " received data: " << d << endl; 
  memory[count] = d;
  count ++; // number of write counts up by 1
  return basic_protocol::SUCCESS;
}

basic_status master1::read( const ADDRESS_TYPE &a , DATA_TYPE &d )
{

  return basic_protocol::SUCCESS;
}
