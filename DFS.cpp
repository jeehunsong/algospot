#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;

void dfs(int here) {
	
	cout << "Visit " << (char)('a' + here) << endl;
	visited[here] = true;

	for (int i = 0; i < adj[here].size(); ++i) {
		if (!visited[adj[here][i]]) {
			dfs(adj[here][i]);
		}
	}
}

void dfsAll() {
	visited = vector<bool>(adj.size(), false);
	for (int i = 0; i < adj.size(); ++i)
		if (!visited[i]) {
			dfs(i);
			cout << endl;
		}
}

int main()
{
	adj.resize(8);
	adj[0].push_back(1);			//ab
	adj[0].push_back('g' - 'a');	//ag
	adj[1].push_back('f' - 'a');	//bf

	adj[2].push_back(3);			//cd
	adj[2].push_back('e' - 'a');	//ce
	adj[2].push_back('h' - 'a');	//ch
	adj[3].push_back('e' - 'a');	//de
	adj[4].push_back('h' - 'a');	//eh
	dfsAll();
}