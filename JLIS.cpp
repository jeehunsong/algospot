#include <iostream>
#include <string.h>
#include <vector>

#define FOR(i,n) for(int i = 0 ; i < n; i++)

using namespace std;

const long long NEGINF = numeric_limits<long long>::min();
int numSeq;
vector<int> A;
vector<int> B;
int cache[101][101];

inline int max(int x, int y)
{
	if (x > y)
	{
		return x;
	}
	return y;
}

int jlis(int indexA, int indexB)
{
	int & ret = cache[indexA + 1][indexB + 1];

	if (ret != -1)
	{
		return ret;
	}
	ret = 2;
	long long a = (indexA == -1 ? NEGINF : A[indexA]);
	long long b = (indexB == -1 ? NEGINF : B[indexB]);
	long long maxElement = max(a, b);

	for (int nextA = indexA + 1; nextA < A.size(); nextA++)
	{
		if (maxElement < A[nextA])
		{
			ret = max(ret, jlis(nextA, indexB) + 1);
		}
	}
	for (int nextB = indexB + 1; nextB < B.size(); nextB++)
	{
		if (maxElement < B[nextB])
		{
			ret = max(ret, jlis(indexA, nextB) + 1);
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
		int wellDepth, rainyDays;
		cin >> wellDepth >> rainyDays;

		A.clear();
		B.clear();
		A.resize(wellDepth);
		B.resize(rainyDays);
		memset(cache, -1, sizeof(cache));

		for (int i = 0; i < wellDepth; i++)
		{
			cin >> A[i];
		}
		for (int i = 0; i < rainyDays; i++)
		{
			cin >> B[i];
		}

		int max = jlis(-1, -1) - 1 - 1;

		cout << max << '\n';
	}
	return 0;
}