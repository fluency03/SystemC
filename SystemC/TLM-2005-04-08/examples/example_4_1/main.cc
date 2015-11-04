
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


#include "master.h"
#include "mem_slave.h"
#include "address_map.h"
#include "router.h"

using utils::router;

using user::master;
using user::mem_slave;

using basic_protocol::basic_request;
using basic_protocol::basic_response;

int sc_main( int argc , char **argv )
{

  master m("master");

  router< ADDRESS_TYPE ,
          basic_request< ADDRESS_TYPE , DATA_TYPE > ,
          basic_response< DATA_TYPE > > router("router" , "master.iport.map");

  mem_slave s1("slave_1");
  mem_slave s2("slave_2");

  m.initiator_port( router.target_port );

  router.r_port( s1.target_port );
  router.r_port( s2.target_port );

  cout << "Finished binding" << endl;

  sc_start( -1 );

  return 0;

}
