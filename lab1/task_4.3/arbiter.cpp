// file name = arbiter.cpp

#include "arbiter.h"

void arbiter::selection()
{

	while (true)
	{

		sel.write(0);
		wait(10, SC_NS);

		sel.write(1);
		wait(10, SC_NS);

	}

}

