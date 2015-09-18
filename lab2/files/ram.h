// file name = ram.h

#include "systemc.h"
#include "string.h"


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

		// FILE *fp = fopen("T1.txt","r"); // open file 
		// if(!fp) {
		// 	cout << "error. cannot find ram initial file." << endl;
		// }

		// buffer = new int[size];
		// int ad;
		// char * value;
		// int i;
		// for (i = 0; i < size; i++) {
		// 	buffer[i] = 0;
		// }
		// while (fscanf(fp, "%d%s", &ad, value) != EOF) {
		// 	buffer[ad] = int(*value) ;
		// 	cout << "address: " << ad << "; " << "value: " << *value;
		// }

		// --------------------------------------------------------

		// if (debug) {
		// 	cout << "Running constructor of " << name() << endl;
		// }

	}

private:
	int * buffer;
	const int size;
	const bool debug;

};

