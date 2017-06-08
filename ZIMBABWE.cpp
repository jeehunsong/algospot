#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <string.h>

#define FOR(i,n)	for(int i = 0 ; i < n ; i++)
//#define DEBUG

using namespace std;

const int MOD = 1000000007;

string e, digits;
int n, m;
int cache[1 << 14][20][2];

int price(int index, int taken, int mod, int less)
{
	if (index == n)
		return (less && mod == 0) ? 1 : 0;
	int& ret = cache[taken][mod][less];
	if (ret != -1)
		return ret;

	ret = 0;
	for (int next = 0; next < n; next++) {
		if ((taken & (1 << next)) == 0) {
			if (!less && e[index] < digits[next])
				continue;
			
			if ((next > 0) && (digits[next - 1] == digits[next]) &&
				((taken & (1 << (next - 1))) == 0))
				continue;

			int nextTaken = taken | (1 << next);
			int nextMod = (mod * 10 + digits[next] - '0') % m;
			int nextLess = less || e[index] > digits[next];
			//for (int j = 0; j < index; j++)
			//	cout << ' ';
			//cout << digits[next] << endl;
			ret += price(index + 1, nextTaken, nextMod, nextLess);
			//for (int j = 0; j < index; j++)
			//	cout << ' ';
			//cout << ret<< " ret" << endl;
			ret %= MOD;
		}
	}
	return ret;
}

int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	while (cases--)
	{
		e.clear();
		digits.clear();
		cin >> e >> m;
		digits = e;
		sort(digits.begin(), digits.end());
		n = e.length();

		memset(cache, -1, sizeof(cache));
		

		cout << (price(0, 0, 0, 0)) << '\n';


	}
	return 0;
}