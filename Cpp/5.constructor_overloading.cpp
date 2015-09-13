// overloading class constructor
#include <iostream>
using namespace std;

class CRectangle 
{
	int width, height;
public:
	CRectangle(int, int);
	CRectangle();
	int area(void) {return (width * height);}
};

CRectangle::CRectangle(int a, int b)
{
	width = a;
	height = b;
}

CRectangle::CRectangle()
{
	width = 5;
	height = 5;
}

int main()
{
	CRectangle rect(3,4);
	CRectangle rectb; //different from CRectangle rectb(); why?
	cout << "rect area: " << rect.area() << endl;
	cout << "rectb area: " << rectb.area() << endl;
	return 0;
}

