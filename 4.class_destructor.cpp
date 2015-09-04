// example on constructor and destructor
#include <iostream>
using namespace std;

class CRectangle 
{
	int *width, *height; // why add * 
public:
	CRectangle(int, int);
	~CRectangle(); // why add ~
	int area() {return (*width * *height);}
};

CRectangle::CRectangle(int a, int b)
{
	width = new int;
	height = new int;
	// what is the difference
	*width = a;
	*height = b;
}

CRectangle::~CRectangle()
{
	delete width;
	delete height;
}

int main()
{
	CRectangle rect(3,4), rectb(5,6); // declaring together or separate? 
	cout << "rect area: " << rect.area() << endl; // the syntax rule? 
	cout << "rectb area: " << rectb.area() << endl;
	return 0;
}

