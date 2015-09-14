// derived classes
#include <iostream>
using namespace std;

// Inheritance allows to create classes which are derived from other classes, 
// so that they automatically include some of its "parent's" members, plus its own.

class CPolygon{
protected: // what do the protected, private, and public mean?
	int width, height;
public:
	void set_values(int a, int b)
		{ width = a; height = b; }
};

class CRectangle: public CPolygon{
public:
	int area()
		{return (width * height);}
};

class CTriangle: public CPolygon{
public:
	int area()
		{return ( width * height / 2);}
};

int main(){
	CRectangle rect;
	CTriangle trgl;
	rect.set_values(4,5);
	trgl.set_values(4,5);
	cout << rect.area() << endl;
	cout << trgl.area() << endl;
	return 0;
}



