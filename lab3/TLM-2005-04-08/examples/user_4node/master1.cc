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
  count(0)
{

  memory = new ADDRESS_TYPE[ 1024 ];

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
    // buffer[ad] = uint8_t(num) ;
    d = uint8_t(num);
    cout << " ====================== node0 ======================= " << endl; 
    cout << "Writing Destination " << ad << " value " << d << endl;
    initiator_port.transfer( ad , d );
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
    // buffer[ad] = uint8_t(num) ;
    d = uint8_t(num);
    cout << " ====================== node1 ======================= " << endl; 
    cout << "Writing Destination " << ad << " value " << d << endl;
    initiator_port.transfer( ad , d );
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
    // buffer[ad] = uint8_t(num) ;
    d = uint8_t(num);
    cout << " ====================== node2 ======================= " << endl; 
    cout << "Writing Destination " << ad << " value " << d << endl;
    initiator_port.transfer( ad , d );
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
    // buffer[ad] = uint8_t(num) ;
    d = uint8_t(num);
    cout << " ====================== node3 ======================= " << endl; 
    cout << "Writing Destination " << ad << " value " << d << endl;
    initiator_port.transfer( ad , d );
    wait();
  }

}

basic_status master1::write( const DATA_TYPE &d )
{

  // cout << name() << " writing @ " << a << " value " << d << endl; 
  memory[count] = d;
  count ++; // number of write counts up by 1
  return basic_protocol::SUCCESS;
}