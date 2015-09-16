// file name = channel.cpp

// #include "channel.h"

// template <class T>
// void hw_fifo<T>::hw_fifo_method(){

// 	if (valid_in.read() && ready_out.read())
// 	{
// 		// store new data item into fifo
// 		_data[ (_first + _items) % _size ] = data_in;
// 		++_items;
// 	}

// 	if (ready_in.read() && valid_out.read())
// 	{
// 		// discard data item that was just read from fifo
// 		--_items;
// 		_first = ( _first + 1) % _size;
// 	}

// 	// update all output signals
// 	ready_out = (_items < _size);
// 	valid_out = (_items > 0);
// 	data_out = _data[_first];

// }










