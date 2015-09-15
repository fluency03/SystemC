// file name = sink.cpp

#include"sink.h"
#include<cctype>
void sink :: sink_p()
     {
       char c;
       cout << endl << endl;
	
       while (true) 
       {
         in->read(c);
	 c=(char)toupper(c);
         cout << c << flush;
       }
     }
