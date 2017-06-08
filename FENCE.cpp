#include <iostream>
#include <string>
#include <vector>

#define FOR(i,n) for(int i = 0 ; i < n; i++)

using namespace std;

vector<int> fence(20000);

inline int max(int x, int y)
{
	if (x > y)
	{
		return x;
	}
	return y;
}

inline int min(int x, int y)
{
	if (x < y)
	{
		return x;
	}
	return y;
}

int solve(int left, int right)
{
	if (left == right)
	{
		return fence[left];
	}
	int mid = (left + right) / 2;
	int ret = max(solve(left, mid), solve(mid + 1, right));

	int lo = mid, hi = mid + 1;
	int height = min(fence[lo], fence[hi]);

	ret = max(ret, height * 2);

	while (left < lo || hi < right)
	{
		if (hi < right && ((lo == left) || (fence[lo - 1] < fence[hi+1])))
		{
			hi++;
			height = min(height, fence[hi]);
		}
		else
		{
			lo--;
			height = min(height, fence[lo]);
		}
		ret = max(ret, height * (hi - lo + 1));
	}
	return ret;
}

int main()
{
	int cases;
	cin >> cases;
	while (cases--)
	{
		int numFence;
		cin >> numFence;
		
		fence.clear();
		fence.resize(numFence);

		cin.ignore();
		for (int i = 0; i < numFence ; i++)
		{
			cin >> fence[i];
		}

		cout << solve(0, numFence - 1) << endl;
	}
	return 0;
}