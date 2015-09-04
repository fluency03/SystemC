// my first pointer
#include <iostream>
using namespace std;

int main()
{
	int firstvalue, secondvalue;
	int *mypointer;		//Declare a pointer type (int*)

	mypointer = &firstvalue;	//mypointer = address of firstvalue
	*mypointer = 10;			//value pointed by mypointer = 10
	mypointer = &secondvalue; 	//mypointer = address of secondvalue
	*mypointer = 20;			//value pointed by mypointer = 20

	cout << "the firstvalue is: " << firstvalue << endl;
	cout << "the secondvalue is: " << secondvalue << endl;

	return 0;
}

