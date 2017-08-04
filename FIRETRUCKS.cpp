// Solve this problem without Textbook

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

vector<vector<pair<int, int> > > adj;
vector<int> placeVector, stationVector;
int numVertex, numEdge, numPlace, numStation;

inline int min(int a, int b) {return a > b ? b : a;}

int solve_dijkstra_each_station() {
	int retVal = 0, numPlaceRemained = numPlace;
	vector<int> dist(numVertex, 10000000);
	vector<bool> visited(numVertex, false);

	for (auto station: stationVector) {
		DEBUGMSG("Station " << station << " is set to visited")
		//visited[station] = true;
		dist[station] = 0;
	}

	while (numPlaceRemained) {
		int closest = 10000000, here;
		for (int i = 0; i < numVertex; ++i) {
			if (dist[i] < closest && !visited[i]) {
				here = i;
				closest = dist[i];
			}
		}
		DEBUGMSG("here " << here << " closest " << closest)

		if (closest == 10000000) break;
		visited[here] = true;
		if (placeVector[here] == 1) {
			retVal += closest;
			--numPlaceRemained;
		}
		for (int i = 0; i < adj[here].size() ; ++i)
		{
			int there = adj[here][i].first;
			if(visited[there]) continue;
			int nextDist = dist[here] + adj[here][i].second;
			dist[there] = min(dist[there], nextDist);
		}
	}

	return retVal;	
}

int solve_dijkstra_each_place() {
	int retVal = 0;
	vector<vector<int> > mindistToPlace(numPlace, vector<int>(numVertex, 10000000));

	for (int idxPlace = 0 ; idxPlace < numPlace ; ++idxPlace){
		int placeToCheck = placeVector[idxPlace];
		vector<int>& mindist = mindistToPlace[idxPlace];
		int mindistToStation = 10000000;
		mindist[placeToCheck] = 0;

		for (int idxPrevPlace = 0; idxPrevPlace < idxPlace ; ++idxPrevPlace)
		{
			int prevPlace = placeVector[idxPrevPlace];

			// prev-here = here-prev
			if (mindist[prevPlace] > mindistToPlace[idxPrevPlace][placeToCheck])
				mindist[prevPlace] = mindistToPlace[idxPrevPlace][placeToCheck];

			// vertex > prev-vertex + prev-here
			for (int vertexToCheck = 0; vertexToCheck < numVertex; ++vertexToCheck)
			{
				if (mindist[vertexToCheck] > mindistToPlace[idxPrevPlace][vertexToCheck] + mindistToPlace[idxPrevPlace][placeToCheck]) {
					mindist[vertexToCheck] = mindistToPlace[idxPrevPlace][vertexToCheck] + mindistToPlace[idxPrevPlace][placeToCheck];
					if (stationVector[vertexToCheck] == 1 && mindistToStation > mindist[vertexToCheck])
						mindistToStation = mindist[vertexToCheck];
				}
			}
		}

		priority_queue<pair<int, int> > pq;
		pq.push(make_pair(0, placeToCheck));

		while(!pq.empty()) {
			int here = pq.top().second;
			int hereDist = -pq.top().first;
			pq.pop();

			DEBUGMSG("here " << here << " hereDist " << hereDist << " vs " << mindist[here])

			if (hereDist > mindist[here] || hereDist > mindistToStation)
				continue;
			for (int i = 0; i < adj[here].size(); ++i)
			{
				int there = adj[here][i].first;
				int thereDist = hereDist + adj[here][i].second;
				if (mindist[there] > thereDist && mindistToStation > thereDist)
				{
					mindist[there] = thereDist;
					if (stationVector[there] == 1){
						mindistToStation = thereDist;
						DEBUGMSG("\tIt's station")
					}
					pq.push(make_pair(-thereDist, there));
					DEBUGMSG("\tthere " << there << " thereDist " << thereDist)
				}
			}
		}
		retVal += mindistToStation;
	}

	return retVal;
}

inline int solve()
{	
	// TIMEOUT Occurs
	//return solve_dijkstra_each_place();

	// Solution
	return solve_dijkstra_each_station();
}

int main() {
	ios_base::sync_with_stdio(false);
	int numCase;
	cin >> numCase;
	do {
		cin >> numVertex >> numEdge >> numPlace >> numStation;

		adj = vector<vector<pair<int, int> > >(numVertex);

		for (int i = 0; i < numEdge; ++i)
		{
			int from, to, dist;
			cin >> from >> to >> dist;
			adj[--from].push_back(make_pair(--to, dist));
			adj[to].push_back(make_pair(from, dist));
		}

		placeVector = vector<int>(numVertex, 0);
		for (int i = 0; i < numPlace; ++i) {
			int input;
			cin >> input;
			placeVector[--input] = 1;
		}

		stationVector = vector<int>(numStation);
		for (int i = 0 ; i < numStation ; ++i){
			cin >> stationVector[i];
			--stationVector[i];
		}

		cout << solve() << '\n';
	} while(--numCase);
}