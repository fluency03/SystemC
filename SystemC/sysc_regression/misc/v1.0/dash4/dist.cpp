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
 
  dist.cpp -- Implementation of the odometers.
 
  Original Author: Ali Dasdan, Synopsys, Inc.
 
 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

// $Log: dist.cpp,v $
// Revision 1.1.1.1  2006/12/15 20:26:24  acg
// systemc_tests-2.3
//
// Revision 1.3  2006/01/19 00:48:19  acg
// Andy Goodrich: Changes for the fact signal write checking is enabled.
//
// Revision 1.2  2006/01/18 00:23:50  acg
// Change over from SC_NO_WRITE_CHECK to sc_write_check_enable() call.
//

#define SC_NO_WRITE_CHECK
#include "systemc.h"
#include "const.h"
#include "dist.h"

bool dist_compute_mod::prev_reset;
double dist_compute_mod::total_compute_dist;
double dist_compute_mod::partial_compute_dist;

// Get the pulses for one distance increment.
void
dist_read_mod::get_dist_proc()
{
  wait();

  bool ok = false;

  while (true) {

    // More than one pulse is needed for a distance increment.  This
    // function collects NUM_PULSES_FOR_DIST_INCR pulses for that
    // purpose.
    AWAIT(NUM_PULSES_FOR_DIST_INCR);

    if (start)
      ok = !ok;
    else
      ok = false;

    ok_for_incr = ok;
  }
}

// Compute total distance.
void
dist_compute_mod::compute_total_proc()
{
  if (start)
    total_compute_dist += 1.0;
  else
    total_compute_dist = 0.0;

  total_dist = total_compute_dist;
}

// Compute partial distance.
void
dist_compute_mod::compute_partial_proc()
{
  if (start) {

    // Implement reset.event():
    if (prev_reset != (bool) reset)
      partial_compute_dist = 0.0;
    else
      partial_compute_dist += 1.0;

    prev_reset = reset;

  }
  else
    partial_compute_dist = 0.0;

  partial_dist = partial_compute_dist;
}

// LCD display driver.
void
dist_lcd_mod::lcd_driver_proc()
{
  if (start) {

    if (total_dist.event())
      total = total_dist * DIST_INCR;

    if (partial_dist.event())
      partial = partial_dist * DIST_INCR;

  }
  else {
    total = 0.0;
    partial = 0.0;
  }
}

// End of file
