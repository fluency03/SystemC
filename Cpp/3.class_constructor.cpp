// example: class constructor
#include <iostream>
using namespace std;

class CRectangle 
{
	int width, height;
public:
	// A class constructor is a special member function of a class that is executed 
	// whenever we create new objects of that class.

	// A constructor will have exact same name as the class and it does not have any 
	// return type at all, not even void. Constructors can be very useful for setting 
	// initial values for certain member variables.
	CRectangle(int, int);
	int area() {return (width*height);}
};

CRectangle::CRectangle(int a, int b)
{
	width = a;
	height =b;
}

int main()
{
	CRectangle rect(3,4);
	CRectangle rectb(5,6);
	cout << "rect area: " << rect.area() << endl;
	cout << "rectb area: " << rectb.area() << endl;
	return 0;
}

