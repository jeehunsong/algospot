#include <queue>
#include <iostream>
#include <vector>

using namespace std;

//#define DEBUG
#ifdef DEBUG
#define DEBUGMSG(msg) 	cout << msg << '\n';
#else
#define DEBUGMSG(msg)
#endif

vector<vector<pair<int, double> > > adj;

double solve(int numComputer) {
	vector<double> mindist(numComputer, -1.0);
	mindist[0] = 1.0;

	priority_queue<pair<double, int> > pq;
	pq.push(make_pair(-1.0, 0));

	while(!pq.empty()) {
		int here = pq.top().second;
		double hereDist = -pq.top().first;
		pq.pop();

		DEBUGMSG("here " << here << " hereDist " << hereDist << " vs " << mindist[here])

		if (mindist[here] >= 0 && hereDist > mindist[here])
			continue;
		for (int i = 0; i < adj[here].size(); ++i)
		{
			int there = adj[here][i].first;
			double thereDist = hereDist * adj[here][i].second;
			if (mindist[there] < 0 || mindist[there] > thereDist)
			{
				mindist[there] = thereDist;
				pq.push(make_pair(-thereDist, there));
				DEBUGMSG("\tthere " << there << " thereDist " << thereDist)
			}
		}
	}
	return mindist[numComputer - 1];
}

int main() {
	ios_base::sync_with_stdio(false);
	int numCase;
	cin >> numCase;
	do {
		int numComputer, numLine;
		cin >> numComputer >> numLine;

		adj.clear();
		adj.resize(numComputer);

		for (int i = 0; i < numLine; ++i)
		{
			int from, to;
			double noise;
			cin >> from >> to >> noise;
			adj[from].push_back(make_pair(to, noise));
			adj[to].push_back(make_pair(from, noise));
		}

		printf("%.10lf\n", solve(numComputer));
	} while(--numCase);
}