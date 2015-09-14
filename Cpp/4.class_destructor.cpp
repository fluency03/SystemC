// example on constructor and destructor
#include <iostream>
using namespace std;

class CRectangle 
{
	int *width, *height; // pointer in c
public:
	CRectangle(int, int);
	
	// A destructor will have exact same name as the class prefixed with a tilde (~) and 
	// it can neither return a value nor can it take any parameters. Destructor can be 
	// very useful for releasing resources before coming out of the program like closing 
	// files, releasing memories etc.
	~CRectangle(); 
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

