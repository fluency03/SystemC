// function template 
#include <iostream>
using namespace std;

template <class T>
T GetMax (T a, T b){
	T result;
	result = (a>b)? a : b;
	return (result);
}

int main() {
	
	int i=5, j=6, k;
	long l=10, m=5, n;

	k = GetMax<int>(i,j);
	n = GetMax<long>(l,m);

// type is not needed. the following works as well. 
	// k = GetMax(i,j);
	// n = GetMax(l,m);

	cout << k << endl;
	cout << n << endl;
	
	return 0;
}


