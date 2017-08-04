#include <queue>
#include <iostream>

using namespace std;

constexpr int INF = 0x7FFFFFFF;

vector<pair<int, int> > adj[7];
vector<int> dijkstra(int src, int numNode)
{
	vector<int> dist(numNode, INF);
	dist[src] = 0;
	priority_queue<pair<int, int> > pq;
	pq.push(make_pair(0, src));
	while(!pq.empty()) {
		int cost = -pq.top().first;
	    int here = pq.top().second;
	    pq.pop();
	    if (dist[here] < cost) continue;
	    for (int i = 0; i < adj[here].size(); ++i)
	    {
	    	int there = adj[here][i].first;
	    	int nextDist = adj[here][i].second + cost;
	    	cout << "here " << here << " there " << there << endl;
	    	if(nextDist < dist[there]) {
	    		cout << "Refresh there " << there << " cost from " << dist[there] << " to " << nextDist << endl;
	    		dist[there] = nextDist;
	    		pq.push(make_pair(-nextDist, there));
	    	}
	    }
	}
	return dist;
}
enum alphabet
{
	ea = 0, eb, ec, ed, ee, ef, eg
};

// Test code
int main()
{
	adj[ea].push_back(make_pair(eb, 5));
	adj[ea].push_back(make_pair(ec, 1));
	
	adj[eb].push_back(make_pair(ed, 1));
	adj[eb].push_back(make_pair(eg, 3));
	adj[eb].push_back(make_pair(ef, 3));

	adj[ec].push_back(make_pair(ed, 2));

	adj[ed].push_back(make_pair(ee, 5));
	adj[ed].push_back(make_pair(ef, 5));

	adj[ef].push_back(make_pair(eg, 2));

	vector<int> dist = dijkstra(ea, 7);

	for(auto i: dist)
		cout << i << " ";

	return 0;
}