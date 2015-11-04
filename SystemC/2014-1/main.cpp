// main.cpp
// This program is not assuming any specific producing rate of any processes, i.e., 
// This program will also work when the producing rate is changed, such as when process1 is slower or process3 is faster. 

#include "systemc.h"

// define the token producing rate of each process 
#define RATE1 2
#define RATE2 3
#define RATE3 4


class top : public sc_module
{

public:
	sc_in<bool> clk;

	SC_HAS_PROCESS(top);

	top(sc_module_name name)
		: sc_module(name), length(11),
		  x_count(0), y_count(0), z_count(0) // initialize the buffer counter
	{

		x = new unsigned int [length];
		y = new unsigned int [length];
		z = new unsigned int [length];

		SC_THREAD(process1);
		SC_THREAD(process2);
		SC_THREAD(process3);

	}

	void process1();
	void process2();
	void process3();

private:
	unsigned int x_count, y_count, z_count; // counter of data in the buffer
	unsigned int *x, *y, *z; // buffer of produced data
	sc_event e1, e2; // event of data produced
	unsigned int length; // length of data sequence

};


void top::process1(){

	unsigned int i=0;

	cout << "x=" << x[0] << " AT time=" << sc_time_stamp() << endl; // initial data of x
	x_count++;

	for(i=1; i<=10; i++) {
		wait(RATE1, SC_NS);
		x[i]=i; 
		cout << "x=" << x[i] << " AT time=" << sc_time_stamp() << endl;
		x_count++;
		e1.notify();
	}

}

void top::process2(){

	cout << "	y=" << y[0] << " AT time=" << sc_time_stamp() << endl; // initial data of y
	y_count++;

	while(true) {
		if (y_count>=x_count) { // if process2 has consumed the newest data of process1
			wait(e1);			// wait for the process1's new data
		}
		else{		
			wait(RATE2, SC_NS); // there are still data can be consumed in the buffer
			y[y_count]=x[y_count]*2;
			cout << "	y=" << y[y_count] << " AT time=" << sc_time_stamp() << endl;
			y_count++;
			e2.notify();
		}
	}

}

void top::process3(){
	
	cout << "		z=" << z[0] << " AT time=" << sc_time_stamp() << endl; // initial data of z
	z_count++;

	while(true) {
		if (z_count>=y_count && z_count>=x_count) { // if process3 has consumed the newest data of process1 and process2
			wait(e2 & e1);							// wait for the new data of process1 and process2
		}
		else{		
			wait(RATE3, SC_NS); // there are still data can be consumed in the buffer  
			z[z_count]=x[z_count]+y[z_count];
			cout << "		z=" << z[z_count] << " AT time=" << sc_time_stamp() << endl;
			z_count++;
		}
	}

}


int sc_main(int argc, char *argv[])
{

	sc_clock clk("c1", 1, SC_NS);

	top top1("Top1");
	top1.clk(clk);

	sc_start(100, SC_NS);

	return 0;

}



