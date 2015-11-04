/*
 *
 * SystemC TLM API Standard Proposal and Examples
 * Copyright Cadence Design Systems Inc 2004
 *
 */

#ifndef BASIC_SLAVE_BASE
#define BASIC_SLAVE_BASE

#include "basic_protocol.h"
#include "tlm.h"

using tlm::tlm_transport_if;
//using basic_protocol::basic_if< typename ADDRESS , typename DATA >::write;

namespace basic_protocol
{

template< class ADDRESS , class DATA >
class basic_slave_base :
  public virtual basic_if< ADDRESS , DATA > ,
  public virtual tlm_transport_if<
    basic_request< ADDRESS , DATA > ,
    basic_response< DATA >
  >
{
using basic_if<ADDRESS , DATA >::write;
public:
  typedef  tlm_transport_if<
    basic_request< ADDRESS , DATA > ,
    basic_response< DATA >
  > if_type;

  basic_response<DATA> transport( const basic_request<ADDRESS,DATA> &request ) {

    basic_response<DATA> response;

    switch( request.type ) {
    case READ :
      response.status = read( request.a , response.d );
      break; 
    case WRITE:
      //response.status = this->write( request.a , request.d );
      response.status = write( request.a , request.d );
      break;
    default :
      response.status = ERROR;
      break; 

    }

    return response;

  }


};

};

#endif
