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

#ifndef MASTER1_HEADER
#define MASTER1_HEADER

#include <systemc.h>

#include "bus_types.h"
#include "basic_initiator_port.h"

using basic_protocol::basic_initiator_port;

namespace user_3master
{

class master1 : public sc_module
{
public:
  master1( sc_module_name module_name );

  SC_HAS_PROCESS( master1 );

  basic_initiator_port<ADDRESS_TYPE, DATA_TYPE> initiator_port;

private:
  void run();
  
};

};

#endif
