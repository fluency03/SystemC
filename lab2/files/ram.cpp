// file name = ram.cpp

#include "ram.h"

void ram::ram_proc()
{
  while(true) {
    wait(); // synchronous to rising edge
    if ( address<0 || address>=0xFFFFFFFF ) {
    	SC_REPORT_ERROR("", "Address is out of range. ");
	}
	else{
		if (CE) {
		    if (WE) {
				buffer[address] = data;
				// cout << "The data written: 0x" 
					// << std::hex << std::uppercase << (int)data << endl;
		    }
		    else {
				data = buffer[address];
				// cout << "The data read: 0x" 
					// << std::hex << std::uppercase << (int)buffer[address] << endl;
		    }
		}
		else{
			if (WE){
				// do nothing
				// cout << "DO NOTHING! " << endl;
			}
			else{
				data = 0xFF;
			}
		}
	}
  }
}

