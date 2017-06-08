#include <iostream>
#include <string>
#include <vector>

#define FOR(i,n)	for(int i = 0 ; i < n ; i++)
#define	INFINITY	1000000000

using namespace std;

int numLong, numShort, question;

inline int min(int a, int b) { return (a > b) ? (b) : (a); }

int com(int n, int r)
{
	int ret = 1;

	r = min(r, (n - r));

	for (int i = 0; i < r; i++)
	{
		ret = ret * (n - i) / (i + 1);
		if (ret > INFINITY)
		{
			ret = INFINITY;
			break;
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
		string solution;
		cin >> numLong >> numShort >> question;


		
		cout << solution << '\n';
	}

	return 0;
}