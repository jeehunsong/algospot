
#include <algorithm>
#include <cmath>

double bisection(double lo, double hi, double(*f)(double), double criterion = 2e-7)
{
	if (f(lo) > 0)
		std::swap(lo, hi);
	
	while (fabs(hi - lo) > criterion) {
		double mid = (lo + hi) / 2;
		double fmid = f(mid);
		if (fmid <= 0)
			lo = mid;
		else
			hi = mid;
	}

	return (lo + hi) / 2;
}

double bisection(double lo, double hi, double(*f)(double), int iteration)
{
	if (f(lo) > 0)
		std::swap(lo, hi);

	for (int i = 0 ; i < iteration ; i++) {
		double mid = (lo + hi) / 2;
		double fmid = f(mid);
		if (fmid <= 0)
			lo = mid;
		else
			hi = mid;
	}

	return (lo + hi) / 2;
}

// Test code
#include <iostream>

int main()
{
	//std::cout << bisection(-10.0, 10.0, [](double x) {return x - 3; }) << std::endl;
	std::cout << bisection(-10.0, 10.0, [](double x) {return x - 3; }, 100) << std::endl;
}