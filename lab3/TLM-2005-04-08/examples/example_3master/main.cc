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
#include "master2.h"
#include "master3.h"
#include "mem_slave.h"

using user_3master::master1;
using user_3master::master2;
using user_3master::master3;
using user_3master::mem_slave;


class top : public sc_module
{
public:
  sc_in<bool> clk;

  top( sc_module_name module_name ):
    sc_module( module_name ), 
    m1("master1"), m2("master2"), m3("master3"), s("slave")
    {

      m1.initiator_port( s.target_port1 );
      m2.initiator_port( s.target_port2 );
      m3.initiator_port( s.target_port3 );

      SC_THREAD(run1);
        sensitive << clk.pos();
        // dont_initialize();
      SC_THREAD(run2);
        sensitive << clk.pos();
        // dont_initialize();
      SC_THREAD(run3);
        sensitive << clk.pos();
        // dont_initialize();

    }

  SC_HAS_PROCESS( top );

  // sc_in<bool> Trig;

private:
  master1 m1;
  master2 m2;
  master3 m3;
  mem_slave s; 

  void run1()
  {

    DATA_TYPE d = 1;
    unsigned int i = 0;

    // cout << " ====================== MASTER1 ======================= " << endl; 
    // cout << " =============== This is data WRITING!! =============== " << endl; 
    for( i = 0; i < 20; i++ )
    {

      cout << " ====================== MASTER1 ======================= " << endl; 
      cout << "Writing Address " << i << " value " << d << endl;
      m1.initiator_port.write( i , d );
      wait();

    }

  }

  void run2()
  {

    DATA_TYPE d = 2;
    unsigned int i = 0;

    // cout << " ====================== MASTER2 ======================= " << endl; 
    // cout << " =============== This is data WRITING!! =============== " << endl; 
    for( i = 0; i < 20; i++ )
    {

      cout << " ====================== MASTER2 ======================= " << endl;
      cout << "Writing Address " << i << " value " << d << endl;
      m2.initiator_port.write( i , d );
      wait();

    }

  }

  void run3()
  {

    DATA_TYPE d;
    unsigned int i = 0;

    // cout << " ====================== MASTER3 ======================= " << endl; 
    // cout << " =============== This is data READING!! =============== " << endl;
    for( i = 0; i < 20; i++ )
    {

      m3.initiator_port.read( i , d );
      cout << " ====================== MASTER3 ======================= " << endl; 
      cout << "Read Address " << i << " got " << d << endl;
      wait();

    }
  }


};



int sc_main( int argc , char **argv )
{

  // master1 m1("master1");
  // master2 m2("master2");
  // master3 m3("master3");
  // mem_slave s("slave");

  // m1.initiator_port( s.target_port1 );
  // m2.initiator_port( s.target_port2 );
  // m3.initiator_port( s.target_port3 );

  // bool b = true;
  // unsigned int i;

  sc_clock clk("c1", 1, SC_NS);
  top top1("top1");
  top1.clk(clk);


  // for( i = 0; i < 20; i++ ){
    // b = !b;
  // }

  sc_start( 100, SC_NS );

  // cout << " =============== Summary from slave_odd =============== " << endl;
  // cout << "#read @ slave_odd: " << s_odd.read_out() << endl;
  // cout << "#write @ slave_odd: " << s_odd.write_out() << endl;

  return 0;

}
