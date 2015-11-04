/*
 *
 * SystemC TLM API Standard Proposal and Examples
 * Copyright Cadence Design Systems Inc 2004
 *
 */

#ifndef PIPELINED_MASTER_HEADER
#define PIPELINED_MASTER_HEADER

#include "pipelined_protocol.h"
#include "bus_types.h"

using tlm::tlm_fifo;

class pipelined_master : 
  public sc_module
{
public:

  pipelined_master( sc_module_name module_name );

  sc_port< address_if > address_port;
  sc_port< data_if > data_port;

  SC_HAS_PROCESS( pipelined_master );

private:
  void address_phase();
  void data_phase();

  bool initiate_read( const ADDRESS_TYPE &a );
  bool initiate_write( const ADDRESS_TYPE &a , const DATA_TYPE &d ); 
  
  tlm_fifo< data_phase_request< DATA_TYPE > > outstanding;

};


#endif
