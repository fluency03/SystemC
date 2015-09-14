//main.cpp
#include "systemc.h"
#include "top.h"
// #include "2.stimulus.h"
// #include "2.adder.h"
// #include "2.monitor.h"


int sc_main(int argc, char* argv[]){

	Top top("top");

	sc_start();

	return 0;
}
