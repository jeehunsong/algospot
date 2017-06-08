#include <iostream>
#include <vector>
#include <map>

using namespace std;
#define nextl '\n'

int numLaunch;
vector<int> timeToWarm, timeToEat;

int main()
{
	ios_base::sync_with_stdio(false);
	
	int numCase;
	cin >> numCase;
	
	while (numCase--)
	{
		//cout << "Num Case " << numCase << nextl;

		cin >> numLaunch;
		//cout << "Num Launch " << numLaunch << nextl;

		timeToWarm.resize(numLaunch);
		timeToEat.resize(numLaunch);
		multimap<int, int> sumTime;
		int sumTimeToWarm = 0, accmTimeToWarm = 0, sol = 0;

		//cout << "Input Time to Warm" << nextl;
		for (int i = 0 ; i < numLaunch ; i++)	{
			cin >> timeToWarm[i];
			sumTimeToWarm += timeToWarm[i];
		}

		//cout << "Input Time to Eat" << nextl;
		for (int i = 0 ; i < numLaunch ; i++)	{
			cin >> timeToEat[i];
			sumTime.insert(make_pair(timeToEat[i], timeToWarm[i]));
		}

		
		for (auto iter = sumTime.rbegin() ; iter != sumTime.rend() ; ++iter) {
			// 이번 도시락 데우고 먹는 시간이 제일 긴지를 체크
			//cout << "Check multimap iter" << iter->first << " " << iter->second << nextl;
			if (sol < (accmTimeToWarm + iter->first + iter->second))	{
				//cout << "Sol " << sol << " is updated with " << (accmTimeToWarm + iter->first + iter->second) << nextl;
				sol = accmTimeToWarm + iter->first + iter->second;
			}
			accmTimeToWarm += iter->second;
		}
		
		//cout << "Solution is ";
		cout << sol << nextl;
		//cout << "Go to next case" << nextl;
	}
}