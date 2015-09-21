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
				// cout << "The data written: 0x" << std::hex << std::uppercase << (int)data << endl;
		    }
		    else {
				data = buffer[address];
				// cout << "The data read: 0x" << std::hex << std::uppercase << (int)buffer[address] << endl;
		    }
		}
		else{
			if (WE){
				// do nothing
			}
			else{
				data = 0xFF;
			}
		}
	}
  }
}


void ram::listingA()
{
	int index;
	uint8_t temp;

	for (index=0; index<size; index++)
	{	
		temp = buffer[index];
		temp = temp | 0x04;
		buffer[index] = temp;
	}

}


void ram::listingB()
{

	int index;
	uint8_t temp;

	for (index=0; index<size; index++)
	{
		temp = buffer[index];

		if(temp == 0x70)
			temp = temp & 0x73;
		else if (temp == 0x67) 
			temp = temp & 0x63;

		buffer[index] = temp;
	}

}
