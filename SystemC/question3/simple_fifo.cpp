// simple_fifo.cpp

#include <systemc.h>

class b_write_if : virtual public sc_interface
{
   public:
     virtual bool write(sc_int<32>) = 0;
     virtual void reset() = 0;
};

class b_read_if : virtual public sc_interface
{
   public:
     virtual bool read(sc_int<32> &) = 0;
     virtual int num_available() = 0;
};

class IF : virtual public b_write_if, virtual public b_read_if
{

};


class fifo_channel : public sc_module, public IF
{
   public:
     fifo_channel(sc_module_name name, int _size) 
      : sc_module(name), num_elements(0), first(0), size(_size) {
        data = new sc_int<32> [size];
     }

     bool write(sc_int<32> c) {
       if (num_elements == size){

          cout << "FALSE! FIFO is FULL!" << endl;
          return false;

       }else {

         data[(first + num_elements) % size] = c;
         ++num_elements;
         // write_event.notify();
         return true;

       }
     }

     bool read(sc_int<32> &c){
       if (num_elements == 0){

          cout << "FALSE! FIFO is EMPTY!" << endl;
          return false;

       } else {

         c = data[first];
         -- num_elements;
         first = (first + 1) % size;
         // read_event.notify();
         return true;

       }
     }

     void reset() { num_elements = first = 0; }

     int num_available() { return num_elements;}

   private:
     int size;
     sc_int<32> *data;
     int num_elements, first;
     sc_event write_event, read_event;
};

class Sender : public sc_module
{
   public:
     sc_port<IF> out;
     bool full;

     SC_HAS_PROCESS(Sender);

     Sender(sc_module_name name) : sc_module(name)
     {
       SC_THREAD(SProcess);

     }

     void SProcess()
     {

        sc_int<32> i=0;

        for(i=1; i<=10; i++){

          if (!(out->write(i))){
            full = true;
            wait(1, SC_NS);
            // i=i-1;
          } else {
            full = false;
          }

          if (full) {
            i=i-1;
          }
          else{
            cout << "Write data:" << i << " @" << sc_time_stamp() << endl;
          }

        }

     }
};

// class Receiver : public sc_module , virtual public fifo_channel
class Receiver : public sc_module 
{
   public:
     sc_export<IF> in;
      sc_out<int> out;

     fifo_channel *fifo_inst;

     SC_HAS_PROCESS(Receiver);

     Receiver(sc_module_name name) : sc_module(name), temp(0)
     {

       fifo_inst = new fifo_channel("Fifo1", 5);
       in.bind(*fifo_inst);

       SC_THREAD(RProcess);
       // sensitive << in;
     
     }

     void RProcess()
     {
        wait(10, SC_NS);
        sc_int<32> c;
        bool empty=false;

        cout << endl << endl;

        while (true) {

         if( !(in->read(c)) ) {
            empty = true;
            wait(1,SC_NS);
          } else {
            empty = false;
          }
          
         if (!empty) {out.write(c + temp);
                  cout << "    Read data:" << c + temp << " @" << sc_time_stamp() << endl;}
         temp=c;
       }
     }

  sc_int<32> temp;
};

class top : public sc_module
{
   public:
     Sender *sender_inst;
     Receiver *receiver_inst;
     sc_signal<int> output;

     top(sc_module_name name) : sc_module(name)
     {

       sender_inst = new Sender("Sender1");
       receiver_inst = new Receiver("Receiver1");

       sender_inst->out.bind(receiver_inst->in);
       receiver_inst->out.bind(output);

     }

};

int sc_main (int, char *[]) {
   top top1("Top1");
   sc_start(25, SC_NS);
   return 0;
}
