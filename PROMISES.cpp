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
		
	} while (--numCase);
}