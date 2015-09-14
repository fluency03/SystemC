//stimulus.cpp
#include "stimulus.h"

void Stimulus::generate() {
	wait(); //wait for positive clock edge
	a = 100; b=200;
	wait();
	a = -100; b=-200;
	wait();
	a = 100; b=-100;
	wait();
	sc_stop(); //stop simulation
}
