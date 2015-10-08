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
#include "master_new.h"
#include "mem_slave.h"
#include "switch_master.h"

using user_switch::master;
using user_switch::master_new;
using user_switch::mem_slave;
using user_switch::switch_master;

int sc_main( int argc , char **argv )
{

  // master m("master");
  master_new m("master_new");
  switch_master switcher("switcher");
  mem_slave s_odd("slave_odd");
  mem_slave s_even("slave_even");

  m.initiator_port( switcher.target_port );
  switcher.initiator_port_odd( s_odd.target_port );
  switcher.initiator_port_even( s_even.target_port );

  sc_start( 1, SC_NS );

  cout << " =============== Summary from slave_odd =============== " << endl;
  cout << "#read @ slave_odd: " << s_odd.read_out() << endl;
  cout << "#write @ slave_odd: " << s_odd.write_out() << endl;

  cout << " =============== Summary from slave_even =============== " << endl;
  cout << "#read @ slave_even: " << s_even.read_out() << endl;
  cout << "#write @ slave_even: " << s_even.write_out() << endl;

  cout << " =============== Summary from switcher =============== " << endl;
  cout << "#transactions from master to slave: " << switcher.write_out() << endl;
  cout << "#transactions from slave to master: " << switcher.read_out() << endl;

  return 0;

}
