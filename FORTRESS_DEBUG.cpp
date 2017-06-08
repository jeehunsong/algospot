#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

int longest;

class Fort
{
private:
	Fort();
public:
	int x, y, radius;
	vector<int> siblings;
	Fort(int x, int y, int radius) : x(x), y(y), radius(radius) {};
	~Fort() {};

	bool isIn(Fort & objFort)
	{
		if (this->radius > objFort.radius) {
			//cout << "Wrong compare" << nextl;
			return false;
		}
		int distSquare = (this->x - objFort.x) * (this->x - objFort.x) + (this->y - objFort.y) * (this->y - objFort.y);
		//cout << "distSquare " << distSquare << " radius " << objFort.radius << nextl;
		if (distSquare < objFort.radius * objFort.radius)
			return true;
		return false;
	}
};

bool compareFort(const Fort & a, const Fort & b)
{
	return a.radius > b.radius;
}

int getDepth(vector<Fort> & fortress, int head)
{
	int retVal = 0;
	vector<int> heights;
	for (auto iter = fortress[head].siblings.begin(); iter != fortress[head].siblings.end(); iter++)
	{
		heights.push_back(getDepth(fortress, *iter) + 1);
	}
	if (heights.size() > 0) {
		sort(heights.begin(), heights.end());
		retVal = heights.back();
		if (heights.size() > 1)
			longest = MAX(longest, heights.back() + heights[heights.size() - 2]);
	}
	return retVal;
}

int getSolution(vector<Fort> & fortress) {
	int retVal = 0;
	longest = 0;

	if (fortress[0].siblings.size() == 0) {
		retVal = 0;
	}
	else {
		retVal = getDepth(fortress, 0);
	}

	return MAX(longest, retVal);
}

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;


	while (numCase--)
	{
		int numFort, x, y, radius;

		cin >> numFort;
		vector<Fort> fortress;
		for (int i = 0; i < numFort; i++)
		{
			cin >> x >> y >> radius;
			fortress.push_back(Fort(x, y, radius));
		}

		sort(fortress.begin(), fortress.end(), compareFort);

		for (int i = 1; i < numFort; i++)
		{
			int j;
			for (j = i - 1; j > 0; j--) {
				if (fortress[i].isIn(fortress[j])) {
					//cout << i << " is in " << j << nextl;
					fortress[j].siblings.push_back(i);
					break;
				}
			}
			if (j == 0) {
				fortress[0].siblings.push_back(i);
			}
		}

		cout << getSolution(fortress) << nextl;
	}

	return 0;
}