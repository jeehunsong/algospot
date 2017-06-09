#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

//inline int max(int a, int b) {return a > b ? a : b;}
//inline int min(int a, int b) {return a > b ? b : a;}

int numGallery, numHall;
vector<vector<int> > adj;
vector<int> isVisited;
int numcctv;

const int CCTV = 2;
const int WATCHED = 1;
const int NONE = 0;
// Return true if this node is connected to cctv
int dfs(int here) {
	int numCase[3] = {0, 0, 0};
	isVisited[here] = 1;

	for(int i = 0 ; i < adj[here].size(); ++i) {
		int there = adj[here][i];
		if(isVisited[there] == 0) {
			++numCase[dfs(there)];

			//if (curRetVal == NONE)
			//{
			//	++numcctv;
				// ***** BUGCHECKED from TEXTBOOK *****
				//return CCTV;
			//}
		}
	}

	if(numCase[NONE] > 0) {
		++numcctv;
		return CCTV;
	}
	if(numCase[CCTV] > 0) {
		return WATCHED;
	}

	return NONE;
}

int solve() {
	numcctv = 0;
	isVisited = vector<int>(numGallery, 0);

	for(int i = 0 ; i < numGallery ; ++i) {
		if (isVisited[i] == 0)
			// ***** BUGCHECKED from TEXTBOOK *****
			// If the HEAD is NONE, need one more cctv
			if (dfs(i) == NONE) {
				++numcctv;
			}
	}

	return numcctv;
}

int main() {
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;
	while (numCase--) {
		cin >> numGallery >> numHall;
		adj = vector<vector<int> >(numGallery);

		for (int i = 0; i < numHall; ++i)
		{
			int here, there;
			cin >> here >> there;
			adj[here].push_back(there);
			adj[there].push_back(here);
		}

		cout << solve() << endl;
	}

	return 0;
}