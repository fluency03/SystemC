// friend class 
#include <iostream>
using namespace std;


class CSquare;


class CRectangle{
	int width, height;
public:
	int area() 
		{return (width * height);}
	void convert(CSquare a);
};


class CSquare{
private:
	int side;
public:
	void set_side(int a) 
		{side = a;}
	friend class CRectangle;
// We declare CRectangle as a friend of CSquare so that CRectangle
// member functions could have access to the protected and private
// members of CSquare, more concretely to CSquare::side, which
// describes the side width of the square.
};


void CRectangle::convert(CSquare a){
	width = a.side;
	height = a.side;
}


int main(){
	CSquare sqr;
	CRectangle rect;
	sqr.set_side(4);
	rect.convert(sqr);
	cout << rect.area();
	return 0;
}















