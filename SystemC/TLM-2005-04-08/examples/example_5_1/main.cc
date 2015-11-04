
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
#include "mem_slave.h"
#include "simple_arb.h"
#include "router.h"

using tlm::tlm_transport_if;
using tlm::tlm_transport_channel;

using basic_protocol::basic_request;
using basic_protocol::basic_response;

using utils::router;
using utils::simple_arb;

using user::switch_master;
using user::mem_slave;

typedef tlm_transport_channel< basic_request< ADDRESS_TYPE , DATA_TYPE > ,
			      basic_response< DATA_TYPE > > arb_channel_type;

int sc_main( int argc , char **argv )
{

  // masters
  
  switch_master m0("master_0" , 0 , 57 );
  switch_master m1("master_1" , 1 , 1000 );

  // channels

  arb_channel_type c0 , c1;

  // arbiter

  simple_arb< basic_request< ADDRESS_TYPE , DATA_TYPE > ,
	      basic_response< DATA_TYPE > >  arb("arb");

  // router

  router< ADDRESS_TYPE ,
            basic_request< ADDRESS_TYPE , DATA_TYPE > ,
            basic_response< DATA_TYPE >
        >  router_module("router" , "master.iport.map" ) ;

  // slaves

  mem_slave s0("slave_0");
  mem_slave s1("slave_1");
 
  // connectivity pattern is master -> channel -> arbiter -> router -> slave

  m0.initiator_port( c0.target_export ); // connect m0 to its channel
  m1.initiator_port( c1.target_export );  // connect m1 to its channel

  arb.master_port[0]( c0.slave_export ); // connect arbiter to channel 0
  arb.master_port[1]( c1.slave_export ); // connect arbiter to channel 1

  arb.slave_port( router_module.target_port ); // connect arbiter to router
  
  router_module.r_port( s0.target_port ); // connect router to slave 0
  router_module.r_port( s1.target_port ); // connect router to slave 1

  // set arbitration priorities ( can be done from file if needed )

  arb.add_interface( &arb.master_port[0] , 3 ); 
  arb.add_interface( &arb.master_port[1] , 2 );

  sc_start( 100 , SC_NS );

  cout << "Finished" << endl;

  return 0;

}
