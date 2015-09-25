// file name = main.cpp

#include "systemc.h"
#include "ram.h"
// #include "testbench.h"
#include <iomanip>
#include <bitset>


int sc_main(int argc, char *argv[])
{
    // instance the memory
    int size = 1040;
    bool debug = false;

	ram ram1("ram1", size, debug, 1);
    ram ram2("ram2", size, debug, 2);

    // trace signals
    sc_trace_file *wf = sc_create_vcd_trace_file("ram_wave");
    sc_trace(wf, ram1.address, "address");
    sc_trace(wf, ram1.data, "data");
    sc_trace(wf, ram1.CE, "CE");
    sc_trace(wf, ram1.WE, "WE");
    sc_trace(wf, ram2.address, "address");
    sc_trace(wf, ram2.data, "data");
    sc_trace(wf, ram2.CE, "CE");
    sc_trace(wf, ram2.WE, "WE");

    // declare the signals
	sc_signal<bool> WE1, WE2, CE1, CE2;
	sc_signal<int> address1, address2;
    sc_signal<uint8_t> data1, data2;

    // name binding
	ram1.CE(CE1);
	ram1.WE(WE1);
	ram1.address(address1);
	ram1.data(data1);
    ram2.CE(CE2);
    ram2.WE(WE2);
    ram2.address(address2);
    ram2.data(data2);

    // initialization signals
    CE1      = 0;
    data1    = 0;
    address1 = 0;
    WE1      = 0;
    CE2      = 0;
    data2    = 0;
    address2 = 0;
    WE2      = 0;
    sc_start(0, SC_NS);



    // start test 
    FILE *t = fopen("T3.txt","r"); // open file 
    if(!t) {
        cout << "ERROR. cannot find T3.txt." << endl;
    }

    CE1 = 1;
    CE2 = 1;

    int ad=0, num=0, error1=0, error2=0, odd1=0, odd2=0;

    while (fscanf(t, "%i %x", &ad, &num) != EOF) {

        WE1 = 0;
        WE2 = 0;
        address1 = ad;
        address2 = ad;
        sc_start(1, SC_NS);
        
        // test RAM1
        if ( (uint8_t)num != data1 )
        {
            cout << "Mismatch: Address " << std::dec << ad 
                 << ", FILE is " << std::hex << std::uppercase << num 
                 << ", RAM1 is " << std::hex << std::uppercase << (int)data1 
                 << ", Odd Parity is " << (data1>>7) << endl;

            // cout << std::bitset<32>(num) << endl;
            // cout << std::bitset<32>(data1) << endl << endl;
            // cout << "odd: " <<  (((uint8_t)num)>>7) << "; " << (data1>>7) << endl;
            if ( (((uint8_t)num)>>7) != (data1>>7) )
                odd1++;

            WE1 = 1;
            data1 = num;
            error1++;
        }

        // test RAM2
        if ( (uint8_t)num != data2 )
        {
            cout << "Mismatch: Address " << std::dec << ad 
                 << ", FILE is " << std::hex << std::uppercase << num 
                 << ", RAM2 is " << std::hex << std::uppercase << (int)data2 
                 << ", Odd Parity is " << (data2>>7) << endl;

            if ( (((uint8_t)num)>>7) != (data2>>7) )
                odd2++;

            WE2 = 1;
            data2 = num;
            error2++;
        }

    }

    cout << "# of Mismatch in RAM1: " << std::dec << error1 << endl;
    cout << "% of Mismatch in RAM1: " << std::setprecision(3) << ((float)error1/1041)*100 << "%" << endl;
    cout << "# of incorrect odd in RAM1: " << std::dec << odd1 << endl;

    cout << "# of Mismatch in RAM2: " << std::dec << error2 << endl;
    cout << "% of Mismatch in RAM2: " << std::setprecision(3) << ((float)error2/1041)*100 << "%" << endl;
    cout << "# of incorrect odd in RAM2: " << std::dec << odd2 << endl;




	return 0;

}


