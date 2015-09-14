// derived classes
#include <iostream>
using namespace std;


// A class that declares or inherits a virtual
// function is called polymorphic class.
class CPolygon{
protected: // what do the protected, private, and public mean?
	int width, height;
public:
	void set_values(int a, int b)
		{ width = a; height = b; }
	// allow CRectangle and CTriangle to implement 
	// different versions of area calculation
	virtual int area()
		{ return 0;}
};

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
	CPolygon poly;

	CPolygon * ppoly1 = &rect; 
	CPolygon * ppoly2 = &trgl;
	CPolygon * ppoly3 = &poly;
	
	ppoly1->set_values(4,5);
	ppoly2->set_values(4,5);
	ppoly3->set_values(4,5);

// Functional overriding: Redefine the virutal
// functions in the derived classes
	cout << ppoly1->area() << endl;
	cout << ppoly2->area() << endl;
	cout << ppoly3->area() << endl;

	return 0;
}




