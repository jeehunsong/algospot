#include <iostream>
#include <vector>

using namespace std;

// adjacency of graph
vector<vector<int> > adj;

// is discovered before?
vector<int> discovered;
// is dfs in the node finished?
vector<int> finished;
// the number of discovered node
int counter;

void dfs2 (int here) {
	discovered[here] = counter++;

	for (int i = 0 ; i < adj[here].size() ; ++i) {
		int there = adj[here][i];
		cout << "(" << here << ", " << there << ") is a ";
		// If it is not discovered yet, visit.
		if (discovered[there] == -1) {
			cout << "tree edge" << endl;
			dfs2(there);
		}
		// If there is visited after here, there is a sibling of here
		else if (discovered[here] < discovered[there]) {
			cout << "forward edge" << endl;
		}
		// If dfs in there is not ended, there is a ancestor of here
		else if (finished[there] == 0) {
			cout << "back edge" << endl;
		}
		// crossed edge
		else {
			cout << "cross edge" << endl;
		}
	}
	finished[here] = 1;
}

void dfs2all() {
	discovered = vector<int>(adj.size(), -1);
	finished = vector<int>(adj.size(), 0);
	counter = 0;

	for (int i = 0; i < adj.size(); ++i)
	{
		if (discovered[i] == -1) {
			dfs2(i);
		}
	}
}

// test code
int main() {
	adj.resize(4);
	adj[0].push_back(1);
	adj[0].push_back(2);
	adj[0].push_back(3);

	adj[1].push_back(2);
	
	adj[2].push_back(1);

	adj[3].push_back(1);
	adj[3].push_back(2);

	dfs2all();
}