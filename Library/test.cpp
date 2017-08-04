//#include "13.2_bisection.cpp"

#include <iostream>

using namespace std;

double f(double x)
{
	return x;
}

int main()
{
	cout << bisection(-1.0, 1.0, f) << endl;

}