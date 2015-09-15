// file name = testbench.cpp

#include"testbench.h"

void driver :: prc_drive(){
	char arr[27]="abcdefghijklmnopqrstuvwxyz";
	int i;
	while(1){
	for(i=0;i<26;i++){
	d_char.write(arr[i]); 
	wait(25,SC_NS);
for(int i=0;i<100000000; i++);// dealy in order to see the output.
}

}
}

void monitor :: prc_monitor(){

	cout<< "AT "<<sc_simulation_time()<<" UART output is : "<<m_char<<endl;
}

