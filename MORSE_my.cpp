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

	for (int i = 0; i < r ; i++)
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

	int totalNum, minPos, maxPos, remain;
	vector<string> sol;

	while (cases--)
	{
		string solution;
		cin >> numLong >> numShort >> question;

		totalNum = numLong + numShort;
		minPos = 1;
		maxPos = com(totalNum, numLong);
		
		FOR(i, totalNum)
		{
			int criterion;
			remain = numLong + numShort;
			criterion = minPos + com(remain - 1, numLong - 1);

			//printf("%d step: min %d max %d criterion %d\n", i, minPos, maxPos, criterion);

			if (question >= criterion || (numLong == 0))
			{
				solution.push_back('o');
				numShort--;
				minPos = criterion;
			}
			else
			{
				solution.push_back('-');
				numLong--;
				maxPos = criterion - 1;
			}
		}

		//cout << solution << '\n';
		sol.push_back(solution);
	}
	for (auto i = sol.begin(); i != sol.end(); i++)
	{
		cout << *i << endl;
	}


	return 0;
}