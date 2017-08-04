// Problem solving of https://algospot.com/judge/problem/read/HANOI4
#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

inline int abs(int a) {return (a > 0) ? a : -a;}
int numDisk;

struct state
{
	vector<vector<int> > pole;

	void initiate() {
		pole.clear();
		pole.resize(4, vector<int>());
	}

	vector<state>* getNextState() {
		vector<state> *retVal;
		retVal = new vector<state>;
		for (int from = 0; from < 4; ++from)
		{
			for (int to = 0; to < 4; ++to)
			{
				if (from != to && !pole[from].empty() && 
					(pole[to].empty() || pole[from].back() < pole[to].back())) {
					state temp;
					temp.pole = pole;
					temp.pole[to].push_back(temp.pole[from].back());
					temp.pole[from].pop_back();
					retVal->push_back(temp);
				}
			}
		}
		return retVal;
	}

	bool operator==(const state& st) {
		return pole == st.pole;
	}

	bool operator<(state& st) {
		return (pole < st.pole);
	}
};

state startState, endState;
map<state, int> statemap;

void getInput(state& st) {
	int numDisk, input;

	for (int i = 0; i < 4; ++i) {
		cin >> numDisk;
		for (int j = 0; j < numDisk; ++j) {
			cin >> input;
			st.pole[i].push_back(input);
		}
	}
}

int getNextDist(int dist) {
	return dist > 0 ? dist + 1 : dist - 1;
}

void solve() {
	queue<state> q;
	statemap.clear();
	statemap.insert(make_pair(startState, 1));
	q.push(startState);
	statemap.insert(make_pair(endState, -1));
	q.push(endState);

	while(!q.empty()) {
	    state here = q.front();
	    q.pop();
	    int dist = statemap[here];
	    vector<state> *nextState = here.getNextState();
	    for (auto there : *nextState) {
	    	// there is not discovered yet
	    	if (statemap.find(there) == statemap.end())
	    	{
	    		statemap.insert(make_pair(there, getNextDist(dist)));
	    	}
	    	// find solution
	    	else if (statemap[here] * statemap[there] < 0) {
	    		cout << (abs(statemap[here]) + abs(statemap[there]) - 1) << endl;
	    	}
	    }
	    delete nextState;
	}
	cout << "SOMETHING WRONG" << endl;
}

int main ()
{
	int numCase;
	cin >> numCase;

	while(numCase--) {
		cin >> numDisk;
		
		getInput(startState);
		getInput(endState);

		solve();
	}	

	return 0;
}