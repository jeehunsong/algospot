#include <iostream>
#include <string>
#include <string.h>

#define FOR(i,n) for(int i = 0 ; i < n; i++)

#define ABS(x)	((x) > 0 ? (x) : -1 * (x))

using namespace std;
string pi;
const int INF = 987654321;

inline int MAX(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}

inline int MIN(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	return b;
}

int difficulty(int a, int b)
{
	string peice = pi.substr(a, b - a + 1);

	if (peice == string(peice.size(), peice.at(0)))
	{
		return 1;
	}

	bool flagProg = true;
	for (int i = 1; i < peice.size() - 1; i++)
	{
		if ((peice[i + 1] - peice[i]) != (peice[1] - peice[0]))
		{
			flagProg = false;
			break;
		}
	}
	if ((flagProg == true) && (ABS(peice[1] - peice[0]) == 1))
	{
		return 2;
	}
	
	bool flagAlt = true;
	for (int i = 2; i < peice.size(); i++)
	{
		if (peice.at(i) != peice.at(i % 2))
		{
			flagAlt = false;
			break;
		}
	}
	if (flagAlt == true)
	{
		return 4;
	}
	
	if (flagProg)
	{
		return 5;
	}

	return 10;
}
int cache[10002];

int memorize(int begin)
{
	if (begin == pi.size())
	{
		return 0;
	}
	int & ret = cache[begin];
	if (ret != -1)
	{
		return ret;
	}
	
	ret = INF;
	for (int i = 3; i < 6; i++)
	{
		if ((begin + i) <= pi.size())
		{
			ret = MIN(ret, memorize(begin + i) + difficulty(begin, begin + i - 1));
		}
	}
	return ret;
}

int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	while (cases--)
	{
		memset(cache, -1, sizeof(cache));
		pi.clear();
		cin >> pi;

		cout << memorize(0) << endl;
	}
	return 0;
}