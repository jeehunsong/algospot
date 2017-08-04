#include <iostream>
#include <vector>

using namespace std;

const int INF = 10000000;
int numGalaxy, numWormhole;
vector<vector<pair<int, int> > > adj;



void solve()
{

}

void solve_my_fail()
{
	vector<int> upper(numGalaxy, INF);
	vector<int> lower(numGalaxy, -INF);
	upper[0] = 0;
	lower[0] = 0;
	bool updatedUpper, updatedLower;

	for (int iteration = 0; iteration < numGalaxy; ++iteration)
	{
		updatedUpper = false;
		updatedLower = false;

		for (int from = 0; from < numGalaxy; ++from)
		{
			for (int idxAdj = 0; idxAdj < adj[from].size(); ++idxAdj)
			{
				int to = adj[from][idxAdj].first;
				int time = adj[from][idxAdj].second;

				if (upper[to] > upper[from] + time) {
					upper[to] = upper[from] + time;
					updatedUpper = true;
				}
				if (lower[to] < lower[from] + time) {
					lower[to] = lower[from] + time;
					updatedLower = true;
				}
			}
		}
		if (!(updatedUpper && updatedLower)) break;
	}
	if (upper[1] > 1000000) {
		cout << "UNREACHABLE\n";
	}
	else {
		if (!updatedUpper) {
			cout << upper[1] << " ";
		}
		else {
			cout << "INFINITY ";
		}

		if (!updatedLower) {
			cout << lower[1] << "\n";
		}
		else {
			cout << "INFINITY\n";
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	int numCase;
	cin >> numCase;
	do
	{
		cin >> numGalaxy >> numWormhole;
		adj = vector<vector<pair<int, int> > >(numGalaxy);

		for (int iWormhole = 0; iWormhole < numWormhole; ++iWormhole)
		{
			int from, to, time;
			cin >> from >> to >> time;
			adj[from].push_back(make_pair(to, time));
		}

		solve();
	} while (--numCase);
}