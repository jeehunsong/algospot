#include <iostream>
#include <vector>

using namespace std;

vector<double> coefficient;

void solve()
{
	double lower = -10.0, upper = 10.0;

	
}

int main()
{
	int numCase;
	cin >> numCase;
	do
	{
		int n;
		cin >> n;
		coefficient = vector<double>(n + 1);

		for (int i = 0; i <= n; ++i)
		{
			cin >> coefficient[i];
		}

		solve();
	} while (--numCase);
}