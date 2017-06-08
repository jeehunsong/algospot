#include <iostream>
#include <set>

using namespace std;
#define nextl '\n'

int main()
{
	ios_base::sync_with_stdio(false);
	
	int numCase;
	cin >> numCase;
	while (numCase--)
	{
		int numString, sol;
		cin >> numString;

		if (numString == 1)
		{
			cin >> sol;
		}
		else {
			multiset<int> lenSet;
		
			for (int i = 0 ; i < numString ; i++)	{
				int temp;
				cin >> temp;
				lenSet.insert(temp);
			}

			sol = 0;
			for (int i = 1 ; i < numString ; i++)
			{
				auto it = lenSet.begin();
				int first = *it;
				lenSet.erase(it);
				it = lenSet.begin();
				int second = *it;
				lenSet.erase(it);
				lenSet.insert(first + second);
				sol += first + second;
				//cout << "1st " << first << " 2nd " << second << " sol " << sol << nextl;
			}
		}
		


		cout << sol << nextl;
	}

	return 0;
}