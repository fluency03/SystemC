#include "systemc.h"
// hello world

SC_MODULE (hello_world) 
{
	SC_CTOR (hello_world){}

	void say_world()
	{
		std::cout << "Hello World ! \n";
	}
};

int sc_main(int argc, char* argv[])
{
	hello_world hello("HELLO");
	hello.say_world();
	return (0);
}

