#include <iostream>
#include <string>

#define FOR(i,n)	for(int i = 0 ; i < n ; i++)

using namespace std;

int gGen, gStart, gNumLetter;

int intPow(int base, int exp)
{
	int retVal = 1;
	while (exp)
	{
		if (exp & 1)
			retVal *= base;
		exp >>= 1;
		base *= base;
	}
	return retVal;
}

int length(int gen)
{
	if (gen == 0)
		return 1;

	return (2 + length(gen - 1) * 2);
}

void dragonCurve(int gen, int start)
{

}

int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	while (cases--)
	{
		cin >> gGen >> gStart >> gNumLetter;

		dragonCurve(0, 0);
	}
	return 0;
}