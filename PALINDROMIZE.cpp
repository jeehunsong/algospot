#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

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

int maxOverlap(const string& forward, const string& backward)
{
	int lenBackward = backward.size(), lenForward = forward.size();
	vector <int> pi = getPartialMatch(backward);		// forward로 넣으면 오답

	int begin = 0, matched = 0;

	while (begin < lenForward) {
		if (matched < lenBackward && forward[begin + matched] == backward[matched]) {
			++matched;
			if (begin + matched == lenForward)
				return matched;
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
		string input;
		getline(cin, input);

		string inputReverse(input.rbegin(), input.rend());
		
		cout << (2 * input.size() - maxOverlap(input, inputReverse)) << nextl;
	}

	return 0;
}