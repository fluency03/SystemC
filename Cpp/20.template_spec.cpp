// template specialization
#include <iostream>
using namespace std;

// class template
template <class T>
class mycontainer{
	T element;
public:
	mycontainer(T arg) { element = arg; }
	T inscrease() { return ++element; }
};


// class template specialization 
// when a specific type is passed as template parameter
template <>
class mycontainer <char>{
	char element;
public:
	mycontainer(char arg) { element = arg; }
	char uppercase()
	{
		if ( (element>='a') && (element<='z') )
			element += 'A'-'a';
		return element;
	}
};


int main(){

	mycontainer<int> myint(7);
	mycontainer<char> mychar('j');

	cout << myint.inscrease() << endl;
	cout << mychar.uppercase() << endl;

	return 0;
}



