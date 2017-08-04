#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<pair<double, double> > base;

void solve()
{
	double sol = 0.0;

	

	sol = floor(sol * 100.0 + 0.5) / 100.0;
	cout << sol << endl;
}

int main()
{
	int numCase;
	cin >> numCase;
	do
	{
		int n;
		cin >> n;

		for (int i = 0; i < n; ++i)
		{
			double x, y;
			cin >> x >> y;
			base.push_back(make_pair(x, y));
		}

		solve();

		base.clear();
	} while (--numCase);
}
