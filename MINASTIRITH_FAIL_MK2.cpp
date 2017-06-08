#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <math.h>

using namespace std;
#define nextl '\n'
#define IMP		"IMPOSSIBLE"
#define MAX(x, y) ((x) > (y) ? (x) : (y))

const int PI = acos(0) * 2;

struct post {
	double start;
	double end;
};

pair<double, double> interval[100];

int main()
{

	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;

	while (numCase--)
	{
		int numPost;
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

			double anglePost = atan(y / x);
			if (x < 0.)
				anglePost += PI;
			else if (y < 0.)
				anglePost += 2 * PI;

			post temp;
			temp.start = anglePost - acos((128. - radius * radius) / (128.));

			temp.start = fmod(temp.start + 2 * PI, 2 * PI);
			temp.end = anglePost + acos((128. - radius * radius) / (128.));
			temp.end = fmod(temp.end + 2 * PI, 2 * PI);

			//cout << "Interval " << temp.start << ", " << temp.end << nextl;

			//printf("x %.1lf y %.1lf angle %.1lf(%.1lf)\n", x, y, anglePost * 180 / PI, acos((128. - radius * radius) / (128.)));

			interval[i] = make_pair(temp.start, temp.end);
		}

		if (bBigPost == true) {
			cout << 1 << nextl;
			continue;
		}

		sort(interval, interval + numPost);

		int minCovering = 1000;
		
		for (int idxStart = 0; idxStart < numPost; ++idxStart) {
			// 0 을 끼는 인터벌일 경우 수행
			if (interval[idxStart].first > interval[idxStart].second) {
				int tempCovering = 1;

				int idx = 0;
				double start = interval[idxStart].second, end = interval[idxStart].first;

				// 시작점이 끝점을 따라잡을 때까지 진행
				while (start < end) {
					// start를 포함하면서 가장 멀리 가는 구간의 끝점을 찾는다.
					double currentMax = -1;

					while (idx < numPost && interval[idx].first <= start) {
						if (interval[idx].first < interval[idx].second)
							currentMax = MAX(currentMax, interval[idx].second);
						else
							currentMax = MAX(currentMax, interval[idx].second + 2 * PI);
						++idx;
					}

					if (currentMax <= start)
					{
						tempCovering = 1000;
						break;
					}
					start = currentMax;
					++tempCovering;
				}

				//갱신
				if (tempCovering < minCovering)
					minCovering = tempCovering;
			}
		}

		if (minCovering == 1000)
			cout << IMP << nextl;
		else
			cout << minCovering << nextl;
	}

	return 0;
}