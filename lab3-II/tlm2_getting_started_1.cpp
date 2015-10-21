
// Filename: tlm2_getting_started_1.cpp

//----------------------------------------------------------------------
//  Copyright (c) 2007-2008 by Doulos Ltd.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//----------------------------------------------------------------------

// Version 2  16-June-2008 - updated for TLM-2.0

// Getting Started with TLM-2.0, Tutorial Example 1

// For a full description, see http://www.doulos.com/knowhow/systemc/tlm2

// Shows the generic payload, sockets, and blocking transport interface.
// Shows the responsibilities of initiator and target with respect to the generic payload.
// Has only dummy implementations of the direct memory and debug transaction interfaces.
// Does not show the non-blocking transport interface.

// Needed for the simple_target_socket
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include "systemc"
using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"

// Initiator module generating generic payload transactions

struct Initiator: sc_module
{
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_initiator_socket<Initiator> socket;

  SC_CTOR(Initiator)
  : socket("socket")  // Construct and name socket
  {
    SC_THREAD(thread_process);
  }

  void thread_process()
  {
    // TLM-2 generic payload transaction, reused across calls to b_transport
    tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
    sc_time delay1 = sc_time(10, SC_NS);
    sc_time delay2 = sc_time(10, SC_NS);

    // Generate a random sequence of writes
    cout << "====================This is the write.====================" << endl;
    for (int i = 0; i < 20; i += 1)
    {

      // tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);
      tlm::tlm_command cmd = tlm::TLM_WRITE_COMMAND;
      if (cmd == tlm::TLM_WRITE_COMMAND) data = (rand() % 256);

      // Initialize 8 out of the 10 attributes, byte_enable_length and extensions being unused
      trans->set_command( cmd );
      trans->set_address( data );
      trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
      trans->set_data_length( 4 );
      trans->set_streaming_width( 4 ); // = data_length to indicate no streaming
      trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
      trans->set_dmi_allowed( false ); // Mandatory initial value
      trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

      cout << "trans = { " << (cmd ? 'W' : 'R') << ", " << dec << i
           << " } , data = " << dec << data << " at time " << sc_time_stamp()
           << " delay = " << delay1 << endl;

      socket->b_transport( *trans, delay1 );  // Blocking transport call

      // Initiator obliged to check response status and delay
      if ( trans->is_response_error() )
        SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

      // Realize the delay annotated onto the transport call
      wait(delay1);
    }


    // Generate a random sequence of reads
    cout << "====================This is the read.====================" << endl;
    for (int i = 0; i < 30; i += 1)
    {

      // tlm::tlm_command cmd = static_cast<tlm::tlm_command>(rand() % 2);
      tlm::tlm_command cmd = tlm::TLM_READ_COMMAND;
      if (cmd == tlm::TLM_READ_COMMAND) data = (rand() % 256);

      // Initialize 8 out of the 10 attributes, byte_enable_length and extensions being unused
      trans->set_command( cmd );
      trans->set_address( data );
      trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
      trans->set_data_length( 4 );
      trans->set_streaming_width( 4 ); // = data_length to indicate no streaming
      trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
      trans->set_dmi_allowed( false ); // Mandatory initial value
      trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

      cout << "trans = { " << (cmd ? 'W' : 'R') << ", " << dec << i
           << " } , data = " << dec << data << " at time " << sc_time_stamp()
           << " delay = " << delay2 << endl;

      socket->b_transport( *trans, delay2 );  // Blocking transport call

      // Initiator obliged to check response status and delay
      if ( trans->is_response_error() )
        SC_REPORT_ERROR("TLM-2", "Response error from b_transport");

      // Realize the delay annotated onto the transport call
      wait(delay2);
    }

  }

  // Internal data buffer used by initiator with generic payload
  int data;
};


// Target module representing a simple memory

struct Memory: sc_module
{
  // TLM-2 socket, defaults to 32-bits wide, base protocol
  tlm_utils::simple_target_socket<Memory> socket;

  enum { SIZE = 256 };

  SC_CTOR(Memory)
  : socket("socket")
  {
    // Register callback for incoming b_transport interface method call
    socket.register_b_transport(this, &Memory::b_transport);

    // Initialize memory with random data
    for (int i = 0; i < SIZE; i++)
      mem[i] = 0x00000000 + i;
  }

  // TLM-2 blocking transport method
  virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& delay )
  {
    tlm::tlm_command cmd = trans.get_command();
    sc_dt::uint64    adr = trans.get_address();
    unsigned char*   ptr = trans.get_data_ptr();
    unsigned int     len = trans.get_data_length();
    unsigned char*   byt = trans.get_byte_enable_ptr();
    unsigned int     wid = trans.get_streaming_width();

    // Obliged to check address range and check for unsupported features,
    //   i.e. byte enables, streaming, and bursts
    // Can ignore DMI hint and extensions
    // Using the SystemC report handler is an acceptable way of signalling an error

    if (adr >= sc_dt::uint64(SIZE) || byt != 0 || len > 4 || wid < len)
      SC_REPORT_ERROR("TLM-2", "Target does not support given generic payload transaction");

    // Obliged to implement read and write commands
    if ( cmd == tlm::TLM_READ_COMMAND ){
      memcpy(ptr, &mem[adr], len);
      cout << "Data: " << dec << mem[adr] << 
              " is read from Address: " << dec << adr << endl;
    }
    else if ( cmd == tlm::TLM_WRITE_COMMAND ){
      memcpy(&mem[adr], ptr, len);
      cout << "Data: " << dec << mem[adr] << 
              " is written into Address: " << dec << adr << endl;
    }

    // Obliged to set response status to indicate successful completion
    trans.set_response_status( tlm::TLM_OK_RESPONSE );
  }

  int mem[SIZE];
};


SC_MODULE(Top)
{
  Initiator *initiator;
  Memory    *memory;

  SC_CTOR(Top)
  {
    // Instantiate components
    initiator = new Initiator("initiator");
    memory    = new Memory   ("memory");

    // One initiator is bound directly to one target with no intervening bus

    // Bind initiator socket to target socket
    initiator->socket.bind( memory->socket );
  }
};


int sc_main(int argc, char* argv[])
{
  Top top("top");
  sc_start();
  return 0;
}

