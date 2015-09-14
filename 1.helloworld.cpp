#include "systemc.h"
// hello world

// SC_MODULE defines a Class
// SC_CTOR declares a class constructor

// hello_world is the module name. 
SC_MODULE (hello_world) 
{
	SC_CTOR (hello_world){}

	void say_world()
	{
		std::cout << "Hello World ! \n";
	}
};

// To process command-line arguments.
// argc: argument count
// argv: argument vector
int sc_main(int argc, char* argv[])
{
	hello_world hello("HELLO"); // why there is a "HELLO"
	hello.say_world();
	return (0);
}

