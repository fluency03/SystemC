
/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2004 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.4 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/


#include "mem_slave.h"

using user_4node::mem_slave;

using basic_protocol::basic_status;

mem_slave::mem_slave( sc_module_name module_name , int k ) :
  sc_module( module_name ) ,
  target_port0("tport0"), target_port1("tport1"),
  target_port2("tport2"), target_port3("tport3"),
  initiator_port0("iport0"), initiator_port1("iport1"),
  initiator_port2("iport2"), initiator_port3("iport3"),
  read_num(0), write_num(0)
{

  target_port0( *this );
  target_port1( *this );
  target_port2( *this );
  target_port3( *this );

  memory = new ADDRESS_TYPE[4];

}

basic_status mem_slave::write( const ADDRESS_TYPE &a , const DATA_TYPE &d )
{

  cout << name() << " pass data: " << d << " to node" << a << endl; 
  if (a==0){
    initiator_port0.write( a , d );
  }
  if (a==1){
    initiator_port1.write( a , d );
  }
  if (a==2){
    initiator_port2.write( a , d );
  }
  if (a==3){
    initiator_port3.write( a , d );
  }
  // write_num ++; // number of write counts up by 1
  return basic_protocol::SUCCESS;
}

basic_status mem_slave::read( const ADDRESS_TYPE &a , DATA_TYPE &d )
{

  return basic_protocol::SUCCESS;
  
}
 
mem_slave::~mem_slave() {

  delete [] memory;

}
