#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int> > adj;

vector<int> bfs(int start) {
	vector<bool> discovered(adj.size(), false);
	queue<int> q;
	vector<int> order;

	q.push(start);
	discovered[start] = true;
	while(!q.empty()) {
		int here = q.front();
		q.pop();

		order.push_back(here);
		for (int i = 0; i < adj[here].size(); ++i)
		{
			int there = adj[here][i];
			if (!discovered[there]) {
				q.push(there);
				discovered[there] = true;
				
			}
		}
	}

	return order;
}

// breadth first search to find distance
vector<int> bfs2(int start, vector<int>& distance, vector<int>& parent) {
	vector<bool> discovered(adj.size(), false);
	queue<int> q;
	vector<int> order;

	q.push(start);
	discovered[start] = true;
	distance[start] = 0;
	parent[start] = start;

	while(!q.empty()) {
		int here = q.front();
		q.pop();

		order.push_back(here);
		for (int i = 0; i < adj[here].size(); ++i)
		{
			int there = adj[here][i];
			if (!discovered[there]) {
				q.push(there);
				discovered[there] = true;
				parent[there] = here;
				distance[there] = distance[here] + 1;
			}
		}
	}

	return order;
}

vector<int> shortestPath(int v, const vector<int>& parent) {
	vector<int> path(1, v);
	while(parent[v] != v) {
	    v = parent[v];
	    path.push_back(v);
	}
	reverse(path.begin(), path.end());
	return path;
}

// test code
int main()
{
	adj.resize(9);
	adj[0].push_back(1);
	adj[0].push_back(3);
	adj[0].push_back(4);
	adj[0].push_back(7);

	adj[1].push_back(2);
	adj[1].push_back(3);

	adj[2].push_back(5);
	adj[2].push_back(6);

	adj[3].push_back(6);

	adj[4].push_back(5);

	adj[6].push_back(8);

	vector<int> order;// = bfs(0);

	// Test BFS
	//order = bfs(0);

	// Test BFS with distance and parent
	vector<int> distance(adj.size()), parent(adj.size());

	order = bfs2(0, distance, parent);

	for (auto item: order)
		cout << (char)('a' + item) << " ";
	cout << endl;

	for (auto item: distance)
		cout << item << " ";
	cout << endl;
	for (auto item: parent)
		cout << (char)('a' + item) << " ";
	cout << endl;

	vector<int> path;
	path = shortestPath(8, parent);
	for (auto item: path)
		cout << (char)('a' + item) << " ";
	cout << endl;
}