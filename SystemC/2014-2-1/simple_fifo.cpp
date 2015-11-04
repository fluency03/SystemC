// simple_fifo.cpp

#include <systemc.h>

class nb_write_if : virtual public sc_interface
{
   public:
     virtual void write(unsigned int) = 0;
     virtual void reset() = 0;
};

class nb_read_if : virtual public sc_interface
{
   public:
     virtual void read(unsigned int &) = 0;
     virtual int num_available() = 0;
};

class IF : virtual public nb_write_if, virtual public nb_read_if
{

};

// class fifo_channel : public sc_module, public nb_write_if, public nb_read_if
class fifo_channel : public sc_module, public IF
{
   public:
     fifo_channel(sc_module_name name) : sc_module(name), num_elements(0), first(0) {}

     void write(unsigned int c) {
       if (num_elements == max){
        cout << "FALSE! The FIFO is FULL!" << endl;
         wait(read_event);
       }
       else{
        cout << "TRUE! FIFO is NOT full." << endl;
       }

       data[(first + num_elements) % max] = c;
       ++ num_elements;
       write_event.notify();
     }

     void read(unsigned int &c){
       if (num_elements == 0){
        cout << "FALSE! The FIFO is EMPTY!" << endl;
         wait(write_event);
       }
       else{
        cout << "TRUE! The FIFO is NOT empty." << endl;
       }

       c = data[first];
       -- num_elements;
       first = (first + 1) % max;
       read_event.notify();
     }

     void reset() { num_elements = first = 0; }

     int num_available() { return num_elements;}

   private:
     enum e { max = 5 };
     unsigned int data[max];
     int num_elements, first;
     sc_event write_event, read_event;
};

class Sender : public sc_module
{
   public:
     sc_port<IF> out;

     SC_HAS_PROCESS(Sender);

     Sender(sc_module_name name) : sc_module(name)
     {
       SC_THREAD(SProcess);
     }

     void SProcess()
     {
       // const char *str =
         // "Visit www.accellera.org and see what SystemC can do for you today!\n";

       // while (*str){
         // out->write(*str++);
         // wait(10, SC_NS);
       // }
        unsigned int i=0;

        for(i=0; i<8; i++){
          out->write(i+1);
          cout << "Write data:" << i+1 << " @" << sc_time_stamp() << endl;
          wait(10, SC_NS);
        }

     }
};

// class Receiver : public sc_module , virtual public fifo_channel
class Receiver : public sc_module 
{
   public:
     sc_export<IF> in;
     // sc_port<IF> out;
     // sc_port<nb_write_if> out;

     fifo_channel *fifo_inst;

     SC_HAS_PROCESS(Receiver);

     Receiver(sc_module_name name) : sc_module(name)
     {

       fifo_inst = new fifo_channel("Fifo1");
       in.bind(*fifo_inst);

       SC_THREAD(RProcess);
     
     }

     void RProcess()
     {
        wait(20, SC_NS);
        unsigned int c;
        cout << endl << endl;

        while (true) {
         in->read(c);
         // cout << c << flush;
         cout << "    Read data:" << c*2 << " @" << sc_time_stamp() << endl;
         wait(10, SC_NS);
       }
     }
};

class top : public sc_module
{
   public:
     Sender *sender_inst;
     Receiver *receiver_inst;

     top(sc_module_name name) : sc_module(name)
     {

       sender_inst = new Sender("Sender1");
       receiver_inst = new Receiver("Receiver1");

       sender_inst->out.bind(receiver_inst->in);
     }
};

int sc_main (int, char *[]) {
   top top1("Top1");
   sc_start();
   return 0;
}
