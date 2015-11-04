// main.cpp

#include "systemc.h"

class top : public sc_module
{

public:
	sc_in<bool> clk;
	sc_in<int> input;
	sc_out<int> output;
	sc_signal<int> y1, y2, y3, z;

	SC_HAS_PROCESS(top);

	top(sc_module_name name)
		: sc_module(name),
		  y1(0), y2(0), y3(0), z(0) 
	{

		SC_THREAD(process1);
			sensitive << clk.pos();
			// dont_initialize();
		SC_THREAD(process2);
			sensitive << clk.pos();
			// dont_initialize();
		SC_THREAD(process3);
			sensitive << clk.pos();
			// dont_initialize();
	}

	void process1();
	void process2();
	void process3();

};


void top::process1(){

	while(true) {
		// wait();
		y1=input+1;
		y2=input-1; 
		cout << "y1=" << y1 << " AT time=" << sc_time_stamp() << endl;
		cout << "	y2=" << y2 << " AT time=" << sc_time_stamp() << endl;

		wait();
	}

}

void top::process2(){

	while(true) {

		y3=y2*2;
		cout << "		y3=" << y3 << " AT time=" << sc_time_stamp() << endl;

		wait();
	}

}

void top::process3(){
	
	while(true) {

		z=y1+y3+1;
		cout << "			z=" << z << " AT time=" << sc_time_stamp() << endl;
		output.write(z);

		wait();
	}

}


class stimulus : public sc_module
{

public:
	sc_in<bool> clk;
	sc_out<int> x;

	SC_HAS_PROCESS(stimulus);

	stimulus(sc_module_name name)
		: sc_module(name) 
	{

		SC_THREAD(run);
		sensitive << clk.pos();

	}

	void run(){
		unsigned int i=0;

		cout << "x out: " << x << " AT time=" << sc_time_stamp() << endl;

		for(i=0; i<=10; i++){

			cout << "x out: " << i*10 << " AT time=" << sc_time_stamp() << endl;
			x.write(i*10);
			wait();
		}
	}

};


class monitor : public sc_module
{

public:
	sc_in<bool> clk;
	sc_in<int> z;

	SC_HAS_PROCESS(monitor);

	monitor(sc_module_name name)
		: sc_module(name)
	{

		SC_THREAD(run);
		sensitive << z ; 

	}

	void run(){
		while(true){
			cout << "					Output sequence is: " << z.read() << " @" << sc_time_stamp() << endl;
			wait();
		}
	}

};



int sc_main(int argc, char *argv[])
{
	sc_signal<int> s1, s2;
	sc_clock clk("c1", 1, SC_NS, 0.5, 1, SC_NS, true);

	top top1("Top1");
	top1.clk(clk);
	top1.input(s1);
	top1.output(s2);

	stimulus sti1("stimulus1");
	sti1.clk(clk);
	sti1.x(s1);

	monitor mon1("monitor1");
	mon1.clk(clk);
	mon1.z(s2);

	sc_start(20, SC_NS);

	return 0;

}



