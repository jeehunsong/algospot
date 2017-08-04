// Solve without textbook

#include <iostream>
#include <vector>

using namespace std;

#define DEBUG

vector<pair<double, double> > hull[2];
double xmin[2], xmax[2];

vector<double> checkIntesection(vector<pair<double, double> > hull, double xCoord)
{
	vector<double> retVal;

	for (int cur = 0; cur < hull.size(); ++cur)
	{
		int next = (cur + 1) % hull.size();

		if (min(hull[cur].first, hull[next].first) <= xCoord &&
			max(hull[cur].first, hull[next].first) >= xCoord) 
		{
			retVal.push_back(hull[cur].second + (hull[next].second - hull[cur].second) / (hull[next].first - hull[cur].first) * (xCoord - hull[cur].first))
		}
	}
}

void solve()
{
	double lower = max(xmin[0], xmin[1]), upper = min(xmax[0], xmax[1]);

	for (int iteration = 0; iteration < 100; ++iteration)
	{
		double leftXCoord = (upper - lower) / 3, rightXCoord = (upper - lower) * 2 / 3;

		vector<double> leftYCoord[2], rightYCoord[2];

		for (int i = 0; i < 2; ++i)
		{
			leftYCoord[i] = checkIntesection(hull[i], leftXCoord);
			rightYCoord[i] = checkIntesection(hull[i], rightXCoord);
		}

		if (leftYCoord[0].size() == 0 || leftYCoord[1].size() == 0 || rightYCoord[0].size() == 0 || rightYCoord[1].size() == 0) {
			cout << 0.0 << endl;
			return;
		}

		// 왼쪽으로 좁히는 경우
		if ()
	}
}

int main()
{
	int nCase;
	cin >> nCase;
	do
	{
		int n, m;
		cin >> n >> m;

		hull[0] = vector<pair<double, double> >(n);
		hull[1] = vector<pair<double, double> >(m);

		xmin[0] = 100.0;
		xmax[0] = -100.0;
		for (int i = 0; i < n; ++i){
			cin >> hull[0][i].first >> hull[0][i].second;
			if (hull[0][i].first < xmin[0])
				xmin[0] = hull[0][i].first;
			if (hull[0][i].fist > xmax[0])
				xmax[0] = hull[0][i].first;
		}
		
		xmin[1] = 100;
		for (int i = 0; i < m; ++i) {
			cin >> hull[1][i].first >> hull[1][i].second;
			if (hull[1][i].first < xmin[1])
				xmin[1] = hull[1][i].first;
			if (hull[1][i].fist > xmax[1])
				xmax[1] = hull[1][i].first;
		}

		solve();
	} while (--nCase);
}