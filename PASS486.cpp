#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int numDivisor, lo, hi;

vector<int> minFactor, numFactor, minFactorPower;

void init() {
	minFactor.resize(10000001, -1);
	numFactor.resize(10000001, -1);
	minFactorPower.resize(10000001, -1);
	for (int i = 2; i < minFactor.size(); ++i)
		minFactor[i] = i;

	for (int i = 2 ; i * i < minFactor.size() ; ++i) {
		if (minFactor[i] == i) {
			for (int j = i * i ; j < minFactor.size(); j += i)
			{
				if (minFactor[j] == j)
					minFactor[j] = i;
			}
		}
	}

	numFactor[1] = 1;
	for (int i = 2; i < numFactor.size(); ++i)
	{
		// In the case of prime i
		if (minFactor[i] == i) {
			numFactor[i] = 2;
			minFactorPower[i] = 1;
		}
		else {
			int q = i / minFactor[i];
			// q is not divided by minfactor of i again
			if (minFactor[q] != minFactor[i]) {
				minFactorPower[i] = 1;
			}
			else {
				minFactorPower[i] = minFactorPower[q] + 1;
			}
			numFactor[i] = numFactor[q] * (minFactorPower[i] + 1) / minFactorPower[i];
		}
	}
}

void solve()
{
	int ret = 0;
	for (int i = lo; i <= hi; ++i)
	{
		if (numFactor[i] == numDivisor)
			ret++;
	}
	cout << ret << endl;
}

int main()
{
	int numCase;
	cin >> numCase;

	init();

	do
	{
		cin >> numDivisor >> lo >> hi;

		solve();
	} while (--numCase);
}