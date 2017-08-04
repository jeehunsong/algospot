#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// adjacency of graph
vector<vector<int> > adj;

// Strongly Connected Component ID
vector<int> sccId;
stack<int> st;
int sccCounter, vertexCounter;
// is discovered before?
vector<int> discovered;

// return earliest node discovered with backword edge or cross edge
int scc (int here) {
	int ret = discovered[here] = vertexCounter++;
	st.push(here);

	for (int i = 0; i < adj[here].size(); ++i)
	{
		int there = adj[here][i];

		// forward edge
		if (discovered[there] == -1)
			ret = min(ret, scc(there));
		// cross edge (if already in SCC, ignore)
		else if (sccId[there] == -1)
			ret = min(ret, discovered[there]);
	}

	// no backward edge
	if (ret == discovered[here]) {
		// Every node in stack is in same SCC
		while(true) {
			int t = st.top();
			st.pop();
			sccId[t] = sccCounter;
			if(t == here) break;
		}
		++sccCounter;
	}
	return ret;
}

vector<int> tarjanScc() {
	sccId = discovered = vector<int>(adj.size(), -1);
	sccCounter = vertexCounter = 0;
	for (int i = 0; i < adj.size(); ++i)
	{
		if (discovered[i] == -1) scc(i);
	}
	return sccId;
}
