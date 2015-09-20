// file name = ram.h

#include "systemc.h"
#include "string.h"

#include <stdlib.h>


SC_MODULE(ram) {

	// sc_in<bool> clock;
	sc_in<bool> WE;   // Write Enable
	sc_in<bool> CE;   // Control Enable
	sc_in<int> address;
	sc_inout<int> data;

	void ram_proc();

	SC_HAS_PROCESS(ram);

	ram(sc_module_name name, int size = 32, bool debug = false) :
		sc_module(name), size(size), debug(debug)
	{

		SC_THREAD(ram_proc);
		sensitive << CE << WE << address;

		// --------------------------------------------------------

		FILE *fp = fopen("T1.txt","r"); // open file 
		if(!fp) {
			cout << "error. cannot find ram initial file." << endl;
		}

		buffer = new int[1040];
		int ad, num, i;
		while (fscanf(fp, "%i %x", &ad, &num) != EOF) {
			// cout << "address: " << ad << "; " << "read value: " << num << endl;
			buffer[ad] = num ;
		}

		for (i = 0; i<10; i++)
			cout << "Some data read from TX.txt: " << "buffer"<<"["<<i<<"] = " << buffer[i] << endl;

		// --------------------------------------------------------

		if (debug) {
			cout << "Running constructor of " << name << endl;
		}

	}

private:
	int * buffer;
	const int size;
	const bool debug;

};

