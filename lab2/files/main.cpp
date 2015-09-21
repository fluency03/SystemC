// file name = main.cpp

#include "systemc.h"
#include "ram.h"
// #include "testbench.h"


int sc_main(int argc, char *argv[])
{
    // instance the memory
    int size = 1040;
    bool debug = false;
	ram ram1("ram1", size, debug);

    // trace signals
    sc_trace_file *wf = sc_create_vcd_trace_file("ram_wave");
    sc_trace(wf, ram1.address, "address");
    sc_trace(wf, ram1.data, "data");
    sc_trace(wf, ram1.CE, "CE");
    sc_trace(wf, ram1.WE, "WE");

    // declare the signals
	sc_signal<bool> WE, CE;
	sc_signal<int> address;
    sc_signal<uint8_t> data;

    // name binding
	ram1.CE(CE);
	ram1.WE(WE);
	ram1.address(address);
	ram1.data(data);

    // initialization signals
    CE      = 0;
    data    = 0;
    address = 0;
    WE      = 0;
    sc_start(0, SC_NS);

    int cnt;
    cnt = 2;

    // test cases
    switch (cnt){
        case 1:
        {
            FILE *t1 = fopen("T1.txt","r"); // open file 
            if(!t1) {
                cout << "ERROR. cannot find T1.txt." << endl;
            }

            CE = 1;

            // set a wrong data for testing
            WE = 1;
            address = 0;
            data = 4;
            sc_start(10, SC_NS);

            // read data
            WE = 0;
            int ad1, num1;
            while (fscanf(t1, "%i %x", &ad1, &num1) != EOF) {
                // buffer[ad] = uint8_t(num) ;
                address = ad1;
                sc_start(1, SC_NS);
                if ( (uint8_t)num1 != data )
                    cout << "Mismatch: Address " << std::dec << ad1 
                         << ", FILE is " << std::hex << std::uppercase << num1 
                         << ", RAM is " << std::hex << std::uppercase << (int)data << endl;
                // else
                    // cout << "Match: Address " << std::dec << ad << ", File " << std::hex << std::uppercase << num 
                                                                // << ", Ram " << std::hex << std::uppercase << (int)data << endl;
            }

            break;
        }
        case 2:
        {

            FILE *t2 = fopen("T2.txt","r"); // open file 
            if(!t2) {
                cout << "ERROR. cannot find T1.txt." << endl;
            }

            CE = 1;

            int ad2, num2;
            while (fscanf(t2, "%i %x", &ad2, &num2) != EOF) {

                WE = 0;
                address = ad2;
                sc_start(1, SC_NS);
                // change the first data in T2.txt: 6C -> 6D
                if ( (uint8_t)num2 != data )
                {
                    cout << "Mismatch: Address " << std::dec << ad2 
                         << ", FILE is " << std::hex << std::uppercase << num2 
                         << ", RAM is " << std::hex << std::uppercase << (int)data << endl;
                    WE = 1;
                    data = num2;
                }

            }

            break;
        }
        case 3: 
        {
         
            WE      = 1;
            address = 0x10;
            data    = 0x11;
            CE      = 1;
            sc_start(5, SC_NS);
         
            CE      = 0;
            sc_start(5, SC_NS);
         
            address = 0x12;
            data    = 0x10;
            CE      = 1;
            sc_start(5, SC_NS);
         
            address = 0x8;
            data    = 0x01;
            sc_start(5, SC_NS);
         
            WE      = 0;
            address = 0x10;
            sc_start(5, SC_NS);
         
            address = 0x1;
            sc_start(5, SC_NS);
         
            address = 0x3;
            sc_start(5, SC_NS);
         
            CE      = 0;
            sc_start(1, SC_NS);

            break;
        }
        
    }

	return 0;

}


