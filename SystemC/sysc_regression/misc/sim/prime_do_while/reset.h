/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2014 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.accellera.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  reset.h -- 

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

                /***************************************/
                /* Interface Filename:	reset.h        */
                /***************************************/

#include "common.h"

SC_MODULE( resetp )
{
  SC_HAS_PROCESS( resetp );

  sc_in_clk clk;

  // Outputs
  sc_signal<bool>& reset;

  // Constructor
  resetp (sc_module_name 	NAME,
	  sc_clock&		TICK,
	  sc_signal<bool>&	RESET )
	
      : 
	reset	(RESET)

  	{
          clk(TICK);
		  SC_CTHREAD( entry, clk.neg() );
        }

  void entry();
};
