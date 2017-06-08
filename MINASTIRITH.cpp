#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>

using namespace std;
#define nextl '\n'
#define IMP		"IMPOSSIBLE"
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))

struct post {
	double start;
	double end;
};

int numPost;
pair<double, double> ranges[100];

int solveLinear(double begin, double end)
{
	int used = 0, idx = 0;

	while (begin < end) {
		double maxCover = -1;
		while (idx < numPost && ranges[idx].first <= begin) {
			maxCover = MAX(maxCover, ranges[idx].second);
			++idx;
		}
		if (maxCover <= begin) return 987654321;
		begin = maxCover;
		++used;
	}
	return used;
}



int main()
{

	ios_base::sync_with_stdio(false);
	const double pi = 2.0 * acos(0);

	int numCase;
	cin >> numCase;

	while (numCase--)
	{
		bool bBigPost = false;
		cin >> numPost;

		
		for (int i = 0; i < numPost; i++) {
			double x, y, radius;
			cin >> x >> y >> radius;
			if (radius >= 16.0)
			{
				bBigPost = true;
				break;
			}

			double loc = fmod(2 * pi + atan2(y, x), 2 * pi);
			double range = 2.0 * asin(radius / 2.0 / 8.0);
			ranges[i] = make_pair(loc - range, loc + range);
		}

		if (bBigPost == true) {
			cout << 1 << nextl;
			continue;
		}

		sort(ranges, ranges + numPost);

		double minVal = 987654321;
		for (int i = 0; i < numPost; i++) {
			if (ranges[i].first <= 0 || ranges[i].second >= 2 * pi) {
				double begin = fmod(ranges[i].second, 2 * pi);
				double end = fmod(ranges[i].first + 2 * pi, 2 * pi);
				minVal = MIN(minVal, 1 + solveLinear(begin, end));
			}
		}

		if (minVal <= numPost)
			cout << minVal << nextl;
		else
			cout << IMP << nextl;
	}

	return 0;
}