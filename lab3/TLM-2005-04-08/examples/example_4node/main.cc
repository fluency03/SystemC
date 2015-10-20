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


#include "master1.h"
#include "mem_slave.h"

using user_4node::master1;
using user_4node::mem_slave;


class top : public sc_module
{
public:
  sc_in<bool> clk;

  top( sc_module_name module_name ):
    sc_module( module_name ), 
    m0("master0", 0), m1("master1", 1), 
    m2("master2", 2), m3("master3", 3), 
    s("slave")
    {

      m0.initiator_port( s.target_port0 );
      m1.initiator_port( s.target_port1 );
      m2.initiator_port( s.target_port2 );
      m3.initiator_port( s.target_port3 );

      s.initiator_port0( m0.target_port );
      s.initiator_port1( m1.target_port );
      s.initiator_port2( m2.target_port );
      s.initiator_port3( m3.target_port );

      m0.clk(clk);
      m1.clk(clk);
      m2.clk(clk);
      m3.clk(clk);

    }

  unsigned int write0() { return m0.offer; }
  unsigned int write1() { return m1.offer; }
  unsigned int write2() { return m2.offer; }
  unsigned int write3() { return m3.offer; }

  unsigned int read0() { return m0.count; }
  unsigned int read1() { return m1.count; }
  unsigned int read2() { return m2.count; }
  unsigned int read3() { return m3.count; }

private:
  master1 m0, m1, m2, m3;
  mem_slave s; 

};



int sc_main( int argc , char **argv )
{

  sc_clock clk("c1", 1, SC_NS);
  top top1("top1");
  top1.clk(clk);

  sc_start( 100, SC_NS );

  cout << " =============== Summary for transmits =============== " << endl;
  cout << "Node0's #transmits: " << top1.write0() << endl;
  cout << "Node1's #transmits: " << top1.write1() << endl;
  cout << "Node2's #transmits: " << top1.write2() << endl;
  cout << "Node3's #transmits: " << top1.write3() << endl;
  cout << " =============== Summary for receives =============== " << endl;
  cout << "Node0's #receives: " << top1.read0() << endl;
  cout << "Node1's #receives: " << top1.read1() << endl;
  cout << "Node2's #receives: " << top1.read2() << endl;
  cout << "Node3's #receives: " << top1.read3() << endl;

  return 0;

}
