#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

int numStatus;
vector<string> status;

vector<int> getPartialMatch(const string& N) {
	int m = N.size();
	vector <int> pi(m, 0);

	int begin = 1, matched = 0;

	while (begin + matched < m) {
		if (N[begin + matched] == N[matched]) {
			++matched;
			pi[begin + matched - 1] = matched;
		}
		else
		{
			if (matched == 0)
				++begin;
			else {
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}
	return pi;
}

int findRotate(const string& a, const string& b)
{
	int lenA = a.size(), lenB = b.size();

	vector<int> pi = getPartialMatch(a);
	int begin = 0, matched = 0;

	while (begin < lenB) {
		if (a[matched] == b[begin + matched]) {
			++matched;
			if (matched == lenA)
				return begin;
		}
		else
		{
			if (matched == 0)
				++begin;
			else
			{
				begin += matched - pi[matched - 1];
				matched = pi[matched - 1];
			}
		}
	}

	return 0;
}

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;
	cin.ignore();

	while (numCase--)
	{
		cin >> numStatus;

		status.resize(numStatus + 1);
		for (int i = 0; i < numStatus + 1; i++)
		{
			cin >> status[i];
		}

		int retVal = 0;
		for (int i = 1; i < numStatus + 1; i++) {
			if (i % 2 == 0)
				retVal += findRotate(status[i], status[i - 1] + status[i - 1]);	//¿ä°Ç ¸ô¶ú³×!
			else 
				retVal += findRotate(status[i - 1], status[i] + status[i]);		//¿©±â±îÁö´Â È¥ÀÚ ÇØ°á!
			
		}
		cout << retVal << nextl;

		status.clear();
	}

	return 0;
}