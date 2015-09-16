// file name = channel.h

#include "systemc.h"

template <class T> class hw_fifo : public sc_module
{

public:
	sc_in<bool> 	clk;

	sc_in<T> 		data_in;
	sc_in<bool> 	valid_in;
	sc_out<bool> 	ready_out;

	sc_out<T> 		data_out;
	sc_out<bool> 	valid_out;
	sc_in<bool> 	ready_in;

	SC_HAS_PROCESS(hw_fifo);

	hw_fifo(sc_module_name name, unsigned size)
		: sc_module(name), 
		  _size(size)
	{
		assert(size > 0);
		_first = _items = 0;
		_data = new T[_size];

		SC_METHOD(hw_fifo_method);
		sensitive << clk.pos();

		ready_out.initialize(true);
		valid_out.initialize(false);
	}

	~hw_fifo() { delete[] _data; }

protected:

	void hw_fifo_method()
	{
		if (valid_in.read() && ready_out.read())
		{
			// store new data item into fifo
			_data[ (_first + _items) % _size ] = data_in;
			++_items;
		}

		if (ready_in.read() && valid_out.read())
		{
			// discard data item that was just read from fifo
			--_items;
			_first = ( _first + 1) % _size;
		}

		// update all output signals
		ready_out = (_items < _size);
		valid_out = (_items > 0);
		data_out = _data[_first];
	}

	unsigned _size, _first, _items;
	T * _data;

};





// ---------------------------------------------------------------------------

template <class T> class hw_fifo_wrapper 
	: public sc_module, 
	  public sc_fifo_in_if <T>,
	  public sc_fifo_out_if <T>
{
public:
	sc_in<bool>			clk;

protected:
	// embedded channels
	sc_signal<T> 		write_data;
	sc_signal<bool> 	write_valid;
	sc_signal<bool> 	write_ready;

	sc_signal<T> 		read_data;
	sc_signal<bool> 	read_valid;
	sc_signal<bool> 	read_ready;

	// embedded module
	hw_fifo<T> hw_fifo_1;

public:
	hw_fifo_wrapper(sc_module_name name, unsigned size)
		: sc_module(name), hw_fifo_1("hw_fifo_1", size)
	{
		hw_fifo_1.clk(clk);

		hw_fifo_1.data_in(write_data);
		hw_fifo_1.valid_in(write_valid);
		hw_fifo_1.ready_out(write_ready);

		hw_fifo_1.data_out(read_data);
		hw_fifo_1.valid_out(read_valid);
		hw_fifo_1.ready_in(read_ready);
	}

	const std::string SayHi() { return "Hi"; } // a normal non-virtual method

	virtual void write(const T& data)
	{
		write_data = data; //Valid on next delta-cycle
		write_valid = true; //Valid on next delta-cycle

		do {
			wait(clk->posedge_event());
		} while (write_ready !=true);

		write_valid = false; //Valid on next delta-cycle
	}

	virtual T read()
	{
		read_ready = true; //Valid on next delta-cycle

		do {
			wait(clk->posedge_event());
		} while (read_valid != true);

		read_ready = false; //Valid on next delta-cycle
		return read_data.read();
	}


	virtual void read(T& d) {d = read();}
	// Provide dummy implementations for unneeded
	// sc_fifo<T> interface methods;
	virtual bool nb_read(T&)
		{ assert(0); return false; }

	virtual bool nb_write(const T&)
		{ assert(0); return false; }

	virtual int num_available() const
		{ assert(0); return 0; }

	virtual int num_free() const
		{ assert(0); return 0; }


	const sc_core::sc_event& data_written_event() const
	{
		static sc_core::sc_event never_notified;
		sc_assert( 0 && "Non-blocking interfaces not supported!" );
		return never_notified;
	}

	const sc_core::sc_event& data_read_event() const
	{
		static sc_core::sc_event never_notified;
		sc_assert( 0 && "Non-blocking interfaces not supported!" );
		return never_notified;
	}










};






