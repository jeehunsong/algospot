#include <iostream>
#include <vector>

using namespace std;

long long nGame, nWin;

long long getRatio(int additional)
{
	return (nWin + additional) * 100 / (nGame + additional);
}

void solve() 
{
	long long curRatio = getRatio(0);
	int lower = 1, upper = 2000000000;

	//cout << "Cur Ratio " << curRatio << "%" << endl;

	if (getRatio(upper) == curRatio) {
		cout << -1 << endl;
		return;
	}
	if (getRatio(lower) > curRatio) {
		cout << 1 << endl;
		return;
	}

	while (1) {
		int mid = (upper + lower) / 2;
		if(getRatio(mid) == curRatio) {
			lower = mid;
		}
		else {
			upper = mid;
		}

		//cout << "Lower " << lower << " Upper " << upper << endl;

		if (lower + 1 >= upper) {
			cout << upper << endl;
			return;
		}
	}
}


int main()
{
	int numCase;
	cin >> numCase;
	do
	{
		cin >> nGame >> nWin;

		solve();
	} while (--numCase);
}