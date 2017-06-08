#include <iostream>
#include <vector>

#define FOR(i,n)	for(int i = 0 ; i < n ; i++)
#define	MOD		10000000

using namespace std;

vector<vector<int>> cache(101, vector<int>(101, -1));

int poly(int n, int first)
{
	//poly(n, first) = first * poly(n - first, 1) + (first + 2 - 1) * poly(n - first, 2) + ... + (n - 1) * poly(n - first, n - first)
	if (n == first)
	{
		//printf("n %d first %d return %d\n", n, first, 1);
		return 1;
	}
	int & ret = cache[n][first];
	if (ret != -1)
	{
		return ret;
	}
	ret = 0;
	for (int second = 1; second <= (n - first) ; second++)
	{
		int add = (first + second - 1) * poly(n - first, second);
		add %= MOD;
		ret += add;
		ret %= MOD;
		//printf("add %d ret %d\n", add, ret);
	}
	
	//printf("n %d first %d return %d\n", n, first, ret);
	return ret;
}

int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	while (cases--)
	{
		int blockNum, sol;

		cin >> blockNum;

		sol = 0;
		for (int first = 1; first <= blockNum; first++)
		{
			sol += poly(blockNum, first);
			sol %= MOD;
		}

		cout << sol << '\n';
	}
	return 0;
}