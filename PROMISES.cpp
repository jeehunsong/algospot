#include <iostream>
#include <vector>

using namespace std;

int numCity, numRoad, numNewroad;
vector<vector<int> > adj;

int main()
{
	int numCase;
	cin >> numCase;
	do
	{
		cin >> numCity >> numRoad, numNewroad;
		adj.clear();
		adj.resize(numCity, vector<int>(numCity, 0xFFFFFFF));

		int from, to, dist;
		for (int i = 0; i < numRoad; ++i)
		{
			cin >> from >> to >> dist;
			adj[from][to] = dist;
			adj[to][from] = dist;
		}

		
	} while (--numCase);
}