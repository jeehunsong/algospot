#include <iostream>
#include <string>
#include <vector>

#define FOR(i,n) for(int i = 0 ; i < n; i++)

#define	MOD			1000000007

using namespace std;

vector<unsigned int> sol(100, -1);

unsigned int tiling(int width)
{
	if (width == 0)
	{
		return 1;
	}

	unsigned int & ret = sol[width - 1];
	
	if (ret != -1)
	{
		return ret;
	}
	if (width == 1)
	{
		return ret = 1;
	}

	ret = (tiling(width - 2) + tiling(width - 1)) % MOD;

	return ret;
}

int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	while (cases--)
	{
		int width;
		unsigned int sol;

		cin >> width;

		sol = tiling(width);

		cout << sol << '\n';
	}
	return 0;
}