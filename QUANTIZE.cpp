#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>

#define FOR(i,n) for(int i = 0 ; i < n; i++)

using namespace std;

const int INF = 987654321;

int wellDepth;
int num[101];
int partialSum[101];
int partialSquareSum[101];
int cache[101][11];

inline int min(int a, int b)
{
	if (a > b)
	{
		return b;
	}
	return a;
}

int minError(int lo, int hi)
{
	int sum, squareSum;
	if (lo > 0)
	{
		sum = partialSum[hi] - partialSum[lo - 1];
		squareSum = partialSquareSum[hi] - partialSquareSum[lo - 1];
	}
	else
	{
		sum = partialSum[hi];
		squareSum = partialSquareSum[hi];
	}

	int rainyDays = (int)(0.5 + (double)sum / (double)(hi - lo + 1));

	int ret = squareSum - 2 * rainyDays * sum + rainyDays * rainyDays * (hi - lo + 1);
	return ret;
}

int quantize(int from, int parts)
{
	//cout << "Quantize from " << from << " parts " << parts << endl;
	if (from == wellDepth)
	{
		return 0;
	}
	if (parts == 0)
	{
		return INF;
	}
	int & ret = cache[from][parts];
	if (ret != -1)
	{
		return ret;
	}
	ret = INF;
	for (int partSize = 1; partSize + from <= wellDepth ; partSize++)
	{
		ret = min(ret, minError(from, from + partSize - 1) + quantize(from + partSize, parts - 1));
		//cout << "Start " << from << " Part " << partSize << " error " << (minError(from, from + partSize - 1) + quantize(from + partSize, parts - 1)) << endl;
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
		int ret, s;
		cin >> wellDepth >> s;

		memset(num, 0, sizeof(num));
		memset(cache, -1, sizeof(cache));
		
		for (int i = 0; i < wellDepth; i++)
		{
			cin >> num[i];
		}

		sort(num, num + wellDepth);
		partialSum[0] = num[0];
		partialSquareSum[0] = num[0] * num[0];

		for (int i = 1; i < wellDepth; i++)
		{
			partialSum[i] = partialSum[i - 1] + num[i];
			partialSquareSum[i] = partialSquareSum[i-1] + num[i] * num[i];
		}

		ret = quantize(0, s);
		
		cout << ret << endl;
	}
	return 0;
}