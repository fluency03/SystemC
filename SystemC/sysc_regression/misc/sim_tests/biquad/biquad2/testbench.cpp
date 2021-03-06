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

  testbench.cpp -- 

  Original Author: Martin Janssen, Synopsys, Inc., 2002-02-15

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/

/* Filename testbench.cc */
/* This is the implementation file for synchronous process `testbench' */

#include "testbench.h"

float gen_sample(float t);

void testbench::entry()
{
  float sample_val;
  float result_val;
  float time;

  FILE *data1 = fopen("Sample", "w");
  FILE *data2 = fopen("Result", "w");

  reset.write(true);
  wait(5);
  reset.write(false);
  wait();

  time = 0.0;
  while (true) {
    sample_val = gen_sample(time);
    sample.write(sample_val);
    wait();
    result_val = result.read();
    fprintf(data1, "%f\t%f\n", time, sample_val);
    fprintf(data2, "%f\t%f\n", time, result_val);
    char buf[BUFSIZ];
    sprintf( buf, "Input = %f\tOutput = %f\t", sample_val, result_val );
    cout << buf << flush;
    time += 1.0;
  }
} // end of entry function


float
gen_step(float t)
{
  if (t < 10.0)
    return (0.0);
  else 
    return (1.0);
}

float
gen_impulse(float t)
{
  if (t == 20.00)
    return (1.00);
  else 
    return (0.00);
}

float
gen_sine(float t, float freq) // freq in Hertz
{
  return sin(6.283185 * freq * t * CLOCK_PERIOD * 1e-9);
}

// This function actually generates the samples
float
gen_sample(float t)
{
  return (gen_sine(t, 100000));
}
