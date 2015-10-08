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


#ifndef SWITCH_MASTER_HEADER
#define SWITCH_MASTER_HEADER

#include <systemc.h>

#include "bus_types.h"
#include "basic_initiator_port.h"
#include "basic_slave_base.h"
#include "basic_protocol.h"

using basic_protocol::basic_initiator_port;
using basic_protocol::basic_status;
using basic_protocol::basic_slave_base;
using tlm::tlm_transport_if;

namespace user_switch
{

class switch_master :  
  public sc_module ,
  public virtual basic_slave_base< ADDRESS_TYPE , DATA_TYPE >
{
public:
  switch_master( sc_module_name module_name );

  // SC_HAS_PROCESS( switch_master );

  basic_initiator_port<ADDRESS_TYPE, DATA_TYPE> initiator_port_odd;
  basic_initiator_port<ADDRESS_TYPE, DATA_TYPE> initiator_port_even;
  sc_export< if_type > target_port;

  basic_status write( const ADDRESS_TYPE & , const DATA_TYPE & );
  basic_status read( const ADDRESS_TYPE & , DATA_TYPE & );

  // return number of read and write transaction through switcher
  unsigned int read_out() {return read_num;};
  unsigned int write_out() {return write_num;};

  unsigned int read_num, write_num;

};

};

#endif
