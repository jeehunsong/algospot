#include <iostream>
#include <string>
#include <vector>

using namespace::std;

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
	int begin, matched;

	// TODO

	return pi;
}

vector<int> kmpSearch(const string& H, const string& N)
{
	int n = H.size(), m = N.size();
	vector<int> ret;

	vector<int> pi = getPartialMatch(N);
	int begin, matched;

	// TODO

	return ret;
}

int main()
{

}