#include <iostream>
#include <string.h>
#include <vector>

#define FOR(i,n)	for(int i = 0 ; i < n ; i++)

using namespace std;

#define	RAINPROB	0.75

int wellDepth, rainyDays;
//int cache[1000][2001];
//double cache2[1001][2001];

vector<vector<double>> cache2;

/*
int climb(int days, int climbed)
{
	if (days == m)
		return climbed >= n ? 1 : 0;
	
	int & ret = cache[days][climbed];
	
	if (ret != -1) 
		return ret;

	return ret = climb(days + 1, climbed + 1) + climb(days + 1, climbed + 2);
}
*/

double climb2(int days, int climbed)
{
	if (days == rainyDays)
	{
		return climbed >= wellDepth ? 1.0 : 0;
	}

	if ((wellDepth - climbed) < 0)
	{
		return 1;
	}

	//int & ret = cache[days][climbed];
	double & ret = cache2[rainyDays - days][wellDepth - climbed ];

	if (ret >= 0)
	{
		return ret;
	}

	return ret = (1.0 - RAINPROB) * climb2(days + 1, climbed + 1) + (RAINPROB) * climb2(days + 1, climbed + 2);
}

int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	//FOR(i, 1001)
	//	FOR(j, 2001)
	//	cache2[i][j] = -1.0;

	
	cache2.resize(1001, vector<double>(2001, -1.0));

	while (cases--)
	{
		cin >> wellDepth >> rainyDays;

		//memset(cache, -1, sizeof(cache));
		//cache2.clear();
		

		double sol = climb2(0, 0);

		printf("%.10lf\n", sol);
	}
	return 0;
}