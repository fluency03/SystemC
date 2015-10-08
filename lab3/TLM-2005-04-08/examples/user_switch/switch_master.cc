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


#include "switch_master.h"

using user_switch::switch_master;

switch_master::switch_master( sc_module_name module_name ) :
  sc_module( module_name ) , 
  initiator_port_odd("iport_odd") ,
  initiator_port_even("iport_even") ,
  target_port("tport") 
{

  target_port( *this );

}

basic_status switch_master::write( const ADDRESS_TYPE &a , const DATA_TYPE &d )
{

  if ((a%2)!=0){
    // cout << name() << " transfer data from master to slave_odd @ " << a << " value " << d << endl; 
    initiator_port_odd.write( a , d );
  }
  else{
    // cout << name() << " transfer data from master to slave_even @ " << a << " value " << d << endl; 
    initiator_port_even.write( a , d );
  }

  write_num ++; // number of write counts up by 1
  return basic_protocol::SUCCESS;
}

basic_status switch_master::read( const ADDRESS_TYPE &a , DATA_TYPE &d )
{

  if ((a%2)!=0){
    initiator_port_odd.read( a , d );
    // cout << name() << " transfer data from slave_odd to master @ " << a << " value " << d << endl; 
  }
  else{
    initiator_port_even.read( a , d );
    // cout << name() << " transfer data from slave_even to master @ " << a << " value " << d << endl; 
  }

  read_num ++; // number of read counts up by 1
  return basic_protocol::SUCCESS;
}


