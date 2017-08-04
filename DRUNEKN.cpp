#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

inline int min(int a, int b) {return a > b ? b : a;}

int numVertex, numEdge;
int timeDrunk[500], adj[500][500];
int W[500][500];

void solve() {
	vector<pair<int, int> > order;
	for (int i = 0; i < numVertex; ++i)
		order.push_back(make_pair(timeDrunk[i], i));
	sort(order.begin(), order.end());

	for (int i = 0; i < numVertex; ++i)
		for (int j = 0; j < numVertex; ++j)
			if (i == j)
				W[i][j] = 0;
			else
				W[i][j] = adj[i][j];

	for (int k = 0; k < numVertex; ++k)
	{
		int w = order[k].second;
		for (int i = 0; i < numVertex; ++i)
		{
			for (int j = 0; j < numVertex; ++j)
			{
				adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
				W[i][j] = min(adj[i][w] + timeDrunk[w] + adj[w][j], W[i][j]);
			}
		}
	}
}

int main()
{
	int from, to, dist, numTest;
	cin >> numVertex >> numEdge;
	for (int i = 0; i < numVertex; ++i)
	{
		for (int j = 0; j < numVertex; ++j)
		{
			adj[i][j] = 0xFFFFFFF;
		}
	}

	for (int i = 0; i < numVertex; ++i)
	{
		cin >> timeDrunk[i];
	}

	for (int i = 0; i < numEdge; ++i)
	{
		cin >> from >> to >> dist;
		adj[--from][--to] = dist;
		adj[to][from] = dist;
	}

	solve();

	cin >> numTest;
	for (int i = 0; i < numTest; ++i)
	{
		cin >> from >> to;
		cout << W[--from][--to] << endl;
	}
}