#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <stack>

using namespace std;

vector<vector<int> > adj;
vector<pair<int, int> > timeTable;
int numTeam;


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
		if (discovered[i] == -1) 
			scc(i);
	}
	return sccId;
}

inline bool notOverlap(pair<int, int>& a, pair<int, int>& b) {
	return (a.second <= b.first || b.second <= a.first);
}

void makeGraph(){
	adj = vector<vector<int> >(numTeam * 4);

	for (int i = 0; i < 2 * numTeam; i += 2)
	{
		int j = i + 1;		// i : weekly, j : montly

		// only one of meeting i or meeting j is held
		adj[i * 2 + 1].push_back(j * 2);			// ~i -> j
		adj[j * 2 + 1].push_back(i * 2);			// ~j -> i
	}

	for (int i = 0; i < 2 * numTeam; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			// if i and j is Overlaped
			if (notOverlap(timeTable[i], timeTable[j]) == false) {
				adj[i * 2].push_back(j * 2 + 1);	// i -> ~j
				adj[j * 2].push_back(i * 2 + 1);	// j -> ~i
			}
		}
	}
	
}

vector<int> solve2SAT() {
	vector<int> tarjan = tarjanScc();

	for (int i = 0; i < adj.size() ; i += 2)
	{

		if (tarjan[i] == tarjan[i + 1])
			return vector<int>();
	}

	vector<int> value(adj.size(), -1);

	vector<pair<int, int> > order;
	for (int i = 0; i < adj.size(); ++i)
	{
		order.push_back(make_pair(-tarjan[i], i));
	}
	// sort opposite to scc
	sort(order.begin(), order.end());

	for (int i = 0; i < adj.size(); ++i)
	{
		int vertex = order[i].second;
		int variable = vertex / 2, isTrue = vertex %2 == 0;

		if (value[variable] != -1)
		{
			continue;
		}
		value[variable] = !isTrue;
	}
	return value;
}

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;
	while(numCase--) {
		cin >> numTeam;
		timeTable.clear();

		for (int idxTeam = 0; idxTeam < numTeam; ++idxTeam)
		{
			int weekStart, weekEnd, monthStart, monthEnd;
			cin >> weekStart >> weekEnd >> monthStart >> monthEnd;

			timeTable.push_back(make_pair(weekStart, weekEnd));		// 2 * k 	: weekly
			timeTable.push_back(make_pair(monthStart, monthEnd));	// 2 * k + 1: montly
		}

		makeGraph();

		vector<int> sol = solve2SAT();

		cout << "*****" << endl;
		for (auto item: sol)
			cout << item << " ";
		cout << endl << "*****" << endl;
	}
	return 0;
}