// derived classes
#include <iostream>
using namespace std;


class CPolygon{
protected: 
	int width, height;
public:
	void set_values(int a, int b)
		{ width = a; height = b; }
	// function without implementation at all; 
	// This is done by appending =0 (equal to zero)
	virtual int area(void) = 0;
};
// all classes that contain at least one pure virtual
// function are abstract base classes

// in abstract base classes at least one of its members lacks implementation
// we cannot create instances (objects) of it.
// e.g., 
// wrong: CPolygon poly;
// correct: CPolygon * ppoly1


class CRectrangle: public CPolygon {
public:
	int area()
		{return ( width * height );}
};

class CTriangle: public CPolygon {
public:
	int area()
		{return ( width * height / 2 );}
};

int main(){
	CRectrangle rect;
	CTriangle trgl;

	CPolygon * ppoly1 = &rect; 
	CPolygon * ppoly2 = &trgl;
	
	ppoly1->set_values(4,5);
	ppoly2->set_values(4,5);

	cout << ppoly1->area() << endl;
	cout << ppoly2->area() << endl;

	return 0;
}




