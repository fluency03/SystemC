// monitor.cpp
#include "monitor.h"

void Monitor::printout(){
	while (true) {
		wait();
		cout << "a = " << a << "; ";
		cout << "b = " << b << "; ";
		cout << "c = " << c << "; " << endl;
	}
}


