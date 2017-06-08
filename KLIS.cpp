#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>

#define FOR(i,n)	for(int i = 0 ; i < n ; i++)

using namespace std;

/*
inline int max(int a, int b)
{
	return (a > b) ? a : b;
}

inline int min(int a, int b)
{
	return (a > b) ? b : a;
}
*/

const int MAX = 2000000000 + 1;

int n, k;
vector<int> element;

int cacheLen[501], cacheCnt[501], S[500];

int lis3(int start)
{
	int & ret = cacheLen[start + 1];

	if (ret != -1) return ret;
	ret = 1;
	for (int next = start + 1; next < n; ++next)
	{
		if (start == -1 || S[start] < S[next])
			ret = max(ret, lis3(next) + 1);
	}

	return ret;
}

int count(int start)
{
	if (lis3(start) == 1) return 1;
	int & ret = cacheCnt[start + 1];
	if (ret != -1) return ret;

	ret = 0;
	for (int next = start + 1; next < n; ++next) {
		if ((start == -1 || S[start] < S[next]) &&
			lis3(start) == lis3(next) + 1)
			ret = min<long long>(MAX, (long long)ret + count(next));
	}
	
	return ret;
}

void reconstruct(int start, int skip, vector<int>& lis) {
	// S[start]를 넣는다.
	if (start != -1) lis.push_back(S[start]);
	// 뒤에 올 수 있는 숫자들과 위치의 목록을 만든다.
	vector<pair<int, int>> followers;
	for (int next = start + 1; next < n; ++next)
		if ((start == -1 || S[start] < S[next]) &&
			lis3(start) == lis3(next) + 1)
		{
			followers.push_back(make_pair(S[next], next));
		}
	sort(followers.begin(), followers.end());

	//k번째 수 찾기
	for (int i = 0; i < followers.size(); i++)
	{
		int idx = followers[i].second;
		int cnt = count(idx);
		if (cnt <= skip)
			skip -= cnt;
		else
		{
			//다음 숫자는 S[idx]
			reconstruct(idx, skip, lis);
			break;
		}
	}
	
}

int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	while (cases--)
	{
		cin >> n >> k;
		
		memset(cacheLen, -1, sizeof(cacheLen));
		memset(cacheCnt, -1, sizeof(cacheCnt));
		memset(S, -1, sizeof(S));

		for (int i = 0 ; i < n; i++)
		{
			cin >> S[i];
		}

		int sol = lis3(-1) - 1;

		int maxCount = count(-1);
		
		cout << sol << endl;

		/*
		for (int j = 0; j < k; j++)
		{
			//해를 재구현하기.
			vector<int> lis;
			reconstruct(-1, j, lis);

			for (auto i = lis.begin(); i != lis.end(); i++)
			{
				cout << *i << ' ';
			}
			cout << '\n';
		}
		*/
		//해를 재구현하기.
		vector<int> lis;
		reconstruct(-1, k - 1, lis);

		for (auto i = lis.begin(); i != lis.end(); i++)
		{
			cout << *i << ' ';
		}
		cout << '\n';
	}
	return 0;
}