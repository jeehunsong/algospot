#include <iostream>
#include <string>
#include <assert.h>

#define FOR(i,n)	for(int i = 0 ; i < n ; i++)

using namespace std;

int gGen, gStart, gNumLetter;
const int MAX = 1000000000 + 1;

inline int min(int a, int b)
{
	return (a > b) ? b : a;
}

int length[51];

void precalc() {
	length[0] = 1;
	for (int i = 1; i <= 50; i++)
	{
		length[i] = min(MAX, length[i - 1] * 2 + 2);
	}
}

const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";

char expand(const string& dragonCurve, int generations, int skip)
{
	//cout << "\tCall " << dragonCurve << ' ' << generations << ' ' << skip << '\n';
	if (generations == 0) {
		assert(skip < dragonCurve.size());
		return dragonCurve[skip];
	}
	for (int i = 0; i < dragonCurve.size(); i++)
	{
		if (dragonCurve[i] == 'X' || dragonCurve[i] == 'Y')
		{
			if (skip >= length[generations])
			{
				skip -= length[generations];
			}
			else if (dragonCurve[i] == 'X')
			{
				return expand(EXPAND_X, generations - 1, skip);
			}
			else
				return expand(EXPAND_Y, generations - 1, skip);
		}
		else if (skip > 0)
		{
			--skip;
		}
		else
			return dragonCurve[i];

	}
	return '#';
}




int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	precalc();

	while (cases--)
	{
		cin >> gGen >> gStart >> gNumLetter;

		for (int i = 0; i < gNumLetter; i++)
		{
			cout << expand("FX", gGen, (i + gStart - 1));
		}
		cout << '\n';
	}
	return 0;
}