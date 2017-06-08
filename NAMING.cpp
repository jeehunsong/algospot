#include <iostream>
#include <string>
#include <vector>

using namespace::std;

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

vector<int> naiveSearch(const string& H, const string& N)
{
	vector<int> ret;

	for (int begin = 0; begin + N.size() < H.size(); begin++)
	{
		bool matched = true;

		for (int i = 0; i < N.size(); ++i)
		{
			if (N.at(i) != H.at(begin + i))
			{
				matched = false;
				break;
			}
		}
		if (matched == true)
			ret.push_back(begin);
	}

	return ret;
}

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

vector<int> kmpSearch(const string& H, const string& N)
{
	int n = H.size(), m = N.size();
	vector<int> ret;

	vector<int> pi = getPartialMatch(N);

	int begin = 0, matched = 0;

	while (begin <= n - m)
	{
		if (matched < m && H[begin + matched] == N[matched]) {
			++matched;
			if (matched == m)
				ret.push_back(begin);
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

	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);

	string father, mother;
	getline(cin, father);
	getline(cin, mother);

	vector<int> pi = getPartialMatch((father + mother));
	int k = (father + mother).size();
	vector<int> ret;

	while (k > 0) {
		ret.push_back(k);
		k = pi[k - 1];
	}

	for (auto i = ret.rbegin(); i != ret.rend(); i++)
	{
		cout << *i << ' ';
	}

	return 0;
}