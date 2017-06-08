#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

int nFriend, nFood;
set<string> setFriend;
vector<vector<int>> eaters;

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;

	while (numCase--)
	{
		cin >> nFriend >> nFood;

		eaters.clear();
		eaters.resize(nFood, vector<int>(0));

		cin.ignore();
		string temp;
		getline(cin, temp);
		stringstream ssFood(temp);
		setFriend.clear();
		while (ssFood >> temp)
			setFriend.insert(temp);

		for (int i = 0; i < nFood; i++) {
			int nEater;
			cin >> nEater;
			for (int j = 0; j < nEater; j++) {
				cin >> temp;
				eaters[i].push_back(distance(setFriend.begin(), setFriend.find(temp)));
			}
		}

	}

	return 0;
}