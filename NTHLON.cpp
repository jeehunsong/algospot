// Solve without Textbook
// Can optimize this with preprocessing in recordVector

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//#define DEBUG
#ifdef DEBUG
#define DEBUGMSG(msg) 	cout << msg << '\n';
#else
#define DEBUGMSG(msg)
#endif

inline int max(int a, int b) {return a > b ? a : b;}
inline int min(int a, int b) {return a > b ? b : a;}
//inline int abs(int x) {return x > 0 ? x : -x;}

int numDiscipline;
vector<pair<int, int> > recordVector;
vector<int> timeDiff_wholeTime;
priority_queue<pair<int, int> > pq;

void solve()
{
	vector<bool> visited(400, false);
	while(true) {
		int minDist = timeDiff_wholeTime[200], here = 200;
		for (int i = 0 ; i < 400 ; ++i) {
			if (timeDiff_wholeTime[i] < minDist && !visited[i]) {
				here = i;
				minDist = timeDiff_wholeTime[i];
			}
		}

		if (minDist == timeDiff_wholeTime[200])
			break;

		DEBUGMSG("Here " << (here - 200) << " minDist" << minDist)
		visited[here] = true;

		for (int i = 0; i < numDiscipline; ++i)
		{
			int there = here + recordVector[i].first - recordVector[i].second;
			if (there >= 0 && there < 400 && !visited[there]) {
				int thereDist = timeDiff_wholeTime[here] + recordVector[i].first;
				DEBUGMSG("\tThere " <<(there - 200) << " thereDist " << thereDist)

				if (timeDiff_wholeTime[there] > thereDist) {
					DEBUGMSG("\t\tThere " <<(there - 200) << " thereDist " << timeDiff_wholeTime[there] << " Refreshed")
					timeDiff_wholeTime[there] = thereDist;
				}
			}
		}
	}
	if (timeDiff_wholeTime[200] == 10000000)
		cout << "IMPOSSIBLE" << '\n';
	else
		cout << timeDiff_wholeTime[200] << '\n';
}

int main()
{
	ios_base::sync_with_stdio(false);
	int numCase;
	cin >> numCase;
	do{
		cin >> numDiscipline;
		recordVector = vector<pair<int, int> >(numDiscipline);
		timeDiff_wholeTime = vector<int>(400, 10000000);
		pq = priority_queue<pair<int, int> >();

		for (int i = 0; i < numDiscipline; ++i)
		{
			cin >> recordVector[i].first >> recordVector[i].second;
			//DEBUGMSG("Input " << recordVector[i].first << " " << recordVector[i].second)

			timeDiff_wholeTime[recordVector[i].first - recordVector[i].second + 200] 
				= min(timeDiff_wholeTime[recordVector[i].first - recordVector[i].second + 200], recordVector[i].first);
			//DEBUGMSG("Timee difference " << (recordVector[i].first - recordVector[i].second) << " whole Time spent " << timeDiff_wholeTime[recordVector[i].first - recordVector[i].second + 200]);
		}

		solve();

	} while (--numCase);
}