#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define	INF		10000000
int N;
vector<pair<int, int > > adj[7];
char idxToChar[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

vector<int> dijkstra(int src)
{
	vector<int> mindist(7, INF);

	mindist[src] = 0;
	priority_queue<pair<int, int> > pq;
	pq.push(make_pair(0, src));
	while(!pq.empty())
	{
		int here = pq.top().second;
		int dist = -pq.top().first;
		pq.pop();

		cout << "priority_queue " << idxToChar[here] << ", " << dist << endl;

		if (dist > mindist[here]) continue;
		for (int i = 0; i < adj[here].size(); ++i)
		{
			int there = adj[here][i].first;
			int theredist = adj[here][i].second + dist;
			cout << "\tCheck " << idxToChar[there] << ", " << theredist << endl;
			if (mindist[there] > theredist) {
				mindist[there] = theredist;
				pq.push(make_pair(-theredist, there));
				cout << "\t\tPush " << idxToChar[there] << ", " << theredist << endl;
			}
		}
	}

	return mindist;
}

enum alphabet
{
	ea=0, eb, ec, ed, ee, ef, eg
};

#define		ADDNODE(src, dst, dist) adj[src].push_back(make_pair(dst, dist)); adj[dst].push_back(make_pair(src, dist))

int main()
{
	ADDNODE(ea, eb, 5);
	ADDNODE(ea, ec, 1);

	ADDNODE(eb, ed, 1);
	ADDNODE(eb, ef, 3);
	ADDNODE(eb, eg, 3);

	ADDNODE(ec, ed, 2);
	
	ADDNODE(ed, ee, 5);
	ADDNODE(ed, ef, 3);

	ADDNODE(ef, eg, 2);

	vector<int> mindist = dijkstra(0);
	for (int i = 0 ; i < mindist.size() ; ++i) {
		cout << idxToChar[i] << ": " << mindist[i] << endl;
	}
}