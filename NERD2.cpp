#include <iostream>
#include <map>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

map<int, int> nerd;

bool isDominated(int p, int q)
{
	auto iter = nerd.lower_bound(p);
	if (iter == nerd.end())
		return false;
	return q < iter->second;
}

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;

	while (numCase--)
	{
		int numPeople, sol = 0;
		cin >> numPeople;
		nerd.clear();
		
		for (int i = 0; i < numPeople; i++)
		{
			int p, q;
			cin >> p >> q;
			
			if (isDominated(p, q) == false)
			{
				auto it = nerd.lower_bound(p);
				if (it != nerd.begin())
				{
					--it;
					while (true)
					{
						if (it->second > q) break;
						if (it == nerd.begin())
						{
							nerd.erase(it);
							break;
						}
						else
						{
							auto jt = it;
							--jt;
							nerd.erase(it);
							it = jt;
						}
					}
				}
				nerd.insert(make_pair(p, q));
			}
			
			sol += nerd.size();
		}
		cout << sol << nextl;
	}

	return 0;
}