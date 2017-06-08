#include <iostream>
#include <string>
#include <string.h>
#include <set>

#define FOR(i,n) for(int i = 0 ; i < n; i++)

using namespace std;

int cache[101][101];
/*
bool match_exhaustive(string & wild, string & test)
{
	int pos = 0;

//	cout << "wildcard: " << wild << "// test: " << test << endl;

	while (pos < test.size() 
		&& pos < wild.size() 
		&& (wild.at(pos) == '?' || wild.at(pos) == test.at(pos)))
	{
		++pos;
	}
	if (pos == wild.size())
	{
		return pos == test.size();
	}
	if (wild.at(pos) == '*')
	{
		for (int skip = 0; pos + skip <= test.size(); skip++)
		{
			if (match_exhaustive(wild.substr(pos + 1), test.substr(pos + skip)))
			{
				return true;
			}
		}
	}
	return false;
}

bool matchMemoized(int w, int s, string & wild, string & test)
{
	int & ret = cache[w][s];

	if (ret != -1)
	{
		return ret;
	}
	//cout << "w: " << w << ", s: " << s << endl;

	while (s < test.size()
		&& w < wild.size()
		&& (wild.at(w) == '?' || wild.at(w) == test.at(s)))
	{
		++w;
		++s;
	}
	if (w == wild.size())
	{
		return ret = (s == test.size());
	}
	if (wild.at(w) == '*')
	{
		for (int skip = 0; s + skip <= test.size() ; skip++)
		{
			if (matchMemoized(w + 1, s + skip, wild, test))
			{
				return ret = 1;
			}
		}
	}
	return ret = 0;
}
*/
int matchMemoized2(int w, int s, string & wild, string & test)
{
	int & ret = cache[w][s];

	if (ret != -1)
	{
		return ret;
	}
	//cout << "w: " << w << ", s: " << s << endl;

	while (s < test.size()
		&& w < wild.size()
		&& (wild.at(w) == '?' || wild.at(w) == test.at(s)))
	{
		return matchMemoized2(w + 1, s + 1, wild, test);
	}

	if (w == wild.size())
	{
		return ret = (s == test.size());
	}
	if (wild.at(w) == '*')
	{
		if (matchMemoized2(w + 1, s, wild, test)
			|| ((s < test.size()) && matchMemoized2(w, s+1, wild, test)))
		{
			return ret = 1;
		}
	}
	return ret = 0;
}

int main()
{
	int cases;
	cin >> cases;
	while (cases--)
	{
		string wild;
		cin >> wild;
		set<string>	solution;

		int numTest;
		cin >> numTest;
		while (numTest--)
		{
			string test;
			cin >> test;

			memset(cache, -1, sizeof(cache));
			//if (match_exhaustive(wild, test))
			//if (matchMemoized(0, 0, wild, test))
			if (matchMemoized2(0, 0, wild, test))
			{
				//cout << "SOLUTION: " << test << endl;
				solution.insert(test);
			}
		}
		for (auto i = solution.begin() ; i != solution.end() ; i++)
		{
			cout << *i << endl;
		}
	}
	return 0;
}