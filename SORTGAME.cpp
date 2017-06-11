#include <map>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<int> input;

// "first vector" needs "second" number of reverse operations
map<vector<int>, int > toSort;

// build toSort for n array (Calculate n! cases)
void precalc(int n)
{
	// ordered array
	vector<int> perm(n);
	for (int i = 0 ; i < n ; ++i) 
		perm[i] = i;

	// queue for bfs
	queue<vector<int> > q;
	q.push(perm);
	toSort[perm] = 0;

	while(!q.empty()) {
	    vector<int> here = q.front();
	    q.pop();
	    int cost = toSort[here];

	    for (int i = 0; i < n; ++i)
	    {
	    	for (int j = i + 2; j <= n; ++j)
	    	{
	    		// reverse from i to j - 1
	    		reverse(here.begin() + i, here.begin() + j);
	    		
	    		// Check whether here is already visited
	    		if (toSort.count(here) == 0)
	    		{
	    			toSort[here] = cost + 1;
	    			q.push(here);
	    		}

	    		// take it back
	    		reverse(here.begin() + i, here.begin() + j);
	    	}
	    }
	}

	// MY COMMENT:
	// Possible improvement
	//		precalc(n) can refer to precalc(k) (k < n) if n-k element is consecutive and in order
	//		0 1 2 3 ... n-k [k unordered] = [k unordered]
	//		To do this, "here" check only unordered part
}

int solve(const vector<int>& perm) {
	int n = perm.size();
	vector<int> fixed(n);
	for (int i = 0; i < n; ++i)
	{
		int smaller = 0;
		for (int j = 0; j < n; ++j)
		{
			if (perm[j] < perm[i])
			{
				++smaller;
			}
		}
		fixed[i] = smaller;
	}
	return toSort[fixed];
}

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;

	for (int i = 1; i <= 8; ++i)
	{
		precalc(i);
	}
	while(numCase--) {
	    int arrayLen;
	    cin >> arrayLen;
	    input.clear();
	    input.resize(arrayLen);

	    for (int i = 0; i < arrayLen; ++i) {
	    	cin >> input[i];
	    }

		cout << solve(input) << endl;
	}
}