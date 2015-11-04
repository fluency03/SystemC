// stack.cpp hierarchical channel


#include "systemc.h"

class stack_write_if: virtual public sc_interface
{
public:
  virtual bool nb_write(char) = 0;  // write a character
  virtual void reset() = 0;         // empty the stack
};

class stack_read_if: virtual public sc_interface
{
public:
  virtual bool nb_read(char&) = 0;  // read a character
};


// this class implements the virtual functions
// in the interfaces
class stack: public sc_module, public stack_write_if, public stack_read_if
{
private:
  char data[20];
  int top;                 // pointer to top of stack

public:
  // constructor
  stack(sc_module_name nm) : sc_module(nm), top(0)
  {
  }

  bool nb_write(char c)
  {
    if (top < 20)
    {
      data[top++] = c;
      return true;
    }
    return false;
  }

  void reset()
  {
    top = 0;
  }

  bool nb_read(char& c)
  {
    if (top > 0)
    {
      c = data[--top];
      return true;
    }
    return false;
  }

  void register_port(sc_port_base& port_,
                            const char* if_typename_)
  {
    cout << "binding    " << port_.name() << " to "
         << "interface: " << if_typename_ << endl;
  }
};


class producer : public sc_module
{
public:

  sc_port<stack_write_if> out;
  sc_in<bool> Clock;

  void do_writes()
  {
    int i = 0;
    const char* TestString = "Hallo,     This Will Be Reversed";
    while (true)
    {
      wait();             // for clock edge
      if (out->nb_write(TestString[i]))
        cout << "W " << TestString[i] << " at "
             << sc_time_stamp() << endl;
      i = (i+1) % 32;
    }
  }

  SC_CTOR(producer)
  {
    SC_THREAD(do_writes);
      sensitive << Clock.pos();
  }
};



class consumer : public sc_module
{
public:

  sc_port<stack_read_if> in;
  sc_in<bool> Clock;

  void do_reads()
  {
    char c;

    while (true)
    {
      wait();             // for clock edge
      in->nb_read(c);
      cout << c;
    }
  }

  SC_CTOR(consumer)
  {
    SC_THREAD(do_reads);
      sensitive << Clock.pos();
  }
};




int sc_main(int argc, char* argv[])
{
  sc_clock ClkFast("ClkFast", 100, SC_NS);
  sc_clock ClkSlow("ClkSlow", 50, SC_NS);

  stack Stack1("S1");

  producer P1("P1");
  P1.out(Stack1);
  P1.Clock(ClkFast);

  consumer C1("C1");
  C1.in(Stack1);
  C1.Clock(ClkSlow);

  sc_start(5000, SC_NS);

  return 0;
}





