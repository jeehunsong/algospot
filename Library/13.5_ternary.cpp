
#include <algorithm>
#include <cmath>

double ternary(double lo, double hi, double(*f)(double), int iteration = 100)
{
	for (int i = 0; i < iteration; i++) {
		double a = (2 * lo + hi) / 3.0;
		double b = (lo + 2 * hi) / 3.0;
		if (f(a) > f(b))
			hi = b;
		else
			lo = a;
	}

	return (lo + hi) / 2.0;
}

// Test code
#include <iostream>

int main()
{
	std::cout << ternary(-10.0, 10.0, [](double x) {return -(x - 3) * (x - 3); }, 100) << std::endl;
}