// file name = testbench.cpp

#include "testbench.h"

void driver::prc_drive()
{
	int arr[9] = {1, 2, 3, 4, 5, 6, 7, 7, 8};
	int i;
	
	while(1)
	{
		for(i=0;i<9;i++)
		{
			d = arr[i]; 
			wait(25,SC_NS);   // if remove this, the program will get stuck
			// for(int i=0;i<100000000; i++);// dealy in order to see the output.
		}

	}
}

void monitor::prc_monitor(){

	cout<< "AT "<< sc_simulation_time() <<" UART output is : "<< m <<endl;
}

