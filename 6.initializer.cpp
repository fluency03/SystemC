// overloading class constructor
#include <iostream>
using namespace std;

// example 1: assignment
class Something
{
private:
	int m_nValue;
	double m_dValue;
	int *m_pnValue;

public:
	Something()
	{
		m_nValue = 0;
		m_dValue = 0.0;
		m_pnValue = 0;
	}
};


// example 2: initialization
class SomethingI
{
private:
	int m_nValueI;
	double m_dValueI;
	int *m_pnValueI;

public:
	SomethingI() : m_nValueI(0), m_dValueI(0.0), m_pnValueI(0)
	{

	}
};


// main
int main()
{
	return 0;
}


