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

class fifo_channel : public sc_module, public nb_write_if, public nb_read_if
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

class producer : public sc_module
{
   public:
     sc_port<nb_write_if> out;

     SC_HAS_PROCESS(producer);

     producer(sc_module_name name) : sc_module(name)
     {
       SC_THREAD(main);
     }

     void main()
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

class consumer : public sc_module
{
   public:
     sc_port<nb_read_if> in;

     SC_HAS_PROCESS(consumer);

     consumer(sc_module_name name) : sc_module(name)
     {
       SC_THREAD(main);
     }

     void main()
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
     fifo_channel *fifo_inst;
     producer *prod_inst;
     consumer *cons_inst;

     top(sc_module_name name) : sc_module(name)
     {
       fifo_inst = new fifo_channel("Fifo1");

       prod_inst = new producer("Producer1");
       prod_inst->out(*fifo_inst);

       cons_inst = new consumer("Consumer1");
       cons_inst->in(*fifo_inst);
     }
};

int sc_main (int, char *[]) {
   top top1("Top1");
   sc_start();
   return 0;
}
