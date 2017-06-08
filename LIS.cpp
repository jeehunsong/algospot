#include <iostream>
#include <string>
#include <vector>

#define FOR(i,n) for(int i = 0 ; i < n; i++)

using namespace std;

int numSeq;
vector<int> seq;
vector<int> cache;

inline int max(int x, int y)
{
	if (x > y)
	{
		return x;
	}
	return y;
}

int lis(const vector<int> & A)
{
	if (A.empty())
	{
		return 0;
	}
	int ret = 0;

	for (int i = 0; i < A.size(); i++)
	{
		vector <int> B;
		for (int j = i + 1; j < A.size(); j++)
		{
			if (A[i] < A[j])
			{
				B.push_back(A[j]);
			}
		}
		ret = max(ret, 1 + lis(B));
	}

	return ret;
}

int lis2(int startPos)
{
	if (cache[startPos] != -1)
	{
		return cache[startPos];
	}

	cache[startPos] = 1;
	for (int i = startPos + 1; i < seq.size(); i++)
	{
		if (seq[i] > seq[startPos])
		{
			cache[startPos] = max(cache[startPos], lis2(i) + 1);
		}
	}
	return cache[startPos];
}

int lis3(int start)
{
	int & ret = cache[start + 1];
	if (ret != -1)
	{
		return ret;
	}
	ret = 1;
	for (int next = start + 1; next < seq.size() ; next++)
	{
		if (start == -1 || (seq[next] > seq[start]))
		{
			ret = max(ret, lis3(next) + 1);
		}
	}
	return ret;
}

int lis4()
{
	//initialize
	cache[0] = seq[0];
	int cacheMaxPos = 0;

	//solve
	for (int start = 1; start < seq.size(); start++)
	{
		
	}
}

int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	while (cases--)
	{
		int maxSeq;
		cin >> numSeq;

		seq.clear();
		seq.resize(numSeq);
		cache.clear();
		cache.resize(numSeq + 1, -1);

		for (int i = 0; i < numSeq; i++)
		{
			cin >> seq[i];
		}

		maxSeq = 0;
		
		//maxSeq = lis(seq);
		
		//for (int begin = 0; begin < seq.size(); begin++)	maxSeq = max(maxSeq, lis2(begin));
		
		maxSeq = lis3(-1) - 1;

		//maxSeq = lis4();

		cout << maxSeq << '\n';
	}
	return 0;
}