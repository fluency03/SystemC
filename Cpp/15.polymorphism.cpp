// derived classes
#include <iostream>
using namespace std;


class CPolygon{
protected: // what do the protected, private, and public mean?
	int width, height;
public:
	void set_values(int a, int b)
		{ width = a; height = b; }
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
	// two pointers that point to objects of class CPolygon (ppoly1 and ppoly2)
	// assign references to rect and trgl to these pointers.
	CPolygon * ppoly1 = &rect; 
	CPolygon * ppoly2 = &trgl;
	// Both *ppoly1 and *ppoly2 are of type CPolygon* and therefore we can only use these 
	// pointers to refer to the members that CRectangle and CTriangle inherit from CPolygon.
	ppoly1->set_values(4,5);
	ppoly2->set_values(4,5);
	// when we call the area() members at the end of the program we have had to use directly
	// the objects rect and trgl instead of the pointers *ppoly1 and *ppoly2.
	cout << rect.area() << endl;
	cout << trgl.area() << endl;
	return 0;
}




