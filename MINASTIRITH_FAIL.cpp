#include <iostream>
#include <vector>
#include <map>
#include <math.h>

using namespace std;
#define nextl '\n'
#define IMP		"IMPOSSIBLE"
#define PI 3.14159265

struct post {
	double start;
	double end;
};

vector<post> postInfo;
map<double, double> interval;

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

		postInfo.clear();
		interval.clear();
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
			
			temp.start = fmod(temp.start + 2 * PI, 2*PI);
			temp.end = anglePost + acos((128. - radius * radius) / (128.));
			temp.end = fmod(temp.end + 2 * PI, 2 * PI);

			//cout << "Interval " << temp.start << ", " << temp.end << nextl;

			//printf("x %.1lf y %.1lf angle %.1lf(%.1lf)\n", x, y, anglePost * 180 / PI, acos((128. - radius * radius) / (128.)));

			interval.insert(make_pair(temp.start, temp.end));
		}

		if (bBigPost == true) {
			cout << 1 << nextl;
			continue;
		}

#if 0
		cout << nextl;
		for (auto iter = interval.begin(); iter != interval.end(); iter++)
			cout << "Interval " << iter->first << ", " << iter->second << nextl;
		cout << nextl;
#endif

		//시작점
		double curEnd = -1, curStart = -1;
		int count = 1;
		for (auto iter = interval.rbegin(); iter != interval.rend(); iter++)
		{
			// End > 0 > Start 로 rollover된 경우, 0이 낀 것.
			if (iter->second < iter->first) {
				//가장 멀리까지 가는 것에서 스타트
				if (curEnd < iter->second) {
					curEnd = iter->second;
					curStart = iter->first;
				}
			}
		}

		if (curEnd < 0.) {
			cout << IMP << nextl;
			continue;
		}
		interval.erase(curStart);
		//printf("Erase (%lf, %lf)\n", curStart, curEnd);

		while (1) {
			count++;
			double tempEnd = -1, tempStart = -1;
			for (auto iter = interval.begin(); iter != interval.end(); iter++) {
				if ((iter->first < iter->second && iter->first < curEnd && curEnd < iter->second)
					|| (iter->first > iter->second && (iter->first < curEnd || curEnd < iter->second)))
				{
					if (tempEnd < iter->second || iter->first > iter->second) {
						tempEnd = iter->second;
						tempStart = iter->first;
					}
				}
			}

			if (tempEnd < 0.) {
				cout << IMP << nextl;
				break;
			}
			else if (tempEnd < tempStart || tempEnd > curStart) {
				//printf("Erase (%lf, %lf)\n", tempStart, tempEnd);
				cout << count << nextl;
				break;
			}
			curEnd = tempEnd;
			interval.erase(tempStart);
			//printf("Erase (%lf, %lf)\n", tempStart, tempEnd);
		}
		//cout << nextl;
	}

	return 0;
}