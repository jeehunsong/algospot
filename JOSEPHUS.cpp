#include <iostream>
#include <string>
#include <list>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

int numPeople, numNext;

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;

	while (numCase--)
	{
#if 0
		cin.ignore();
		string temp;
		getline(cin, temp);
#endif
		cin >> numPeople >> numNext;

		list<int> list(numPeople);
		int i = 1;
		for (auto iter = list.begin(); iter != list.end(); iter++)
		{
			*iter = i++;
		}

		auto iter = list.begin();
		while (list.size() > 2) {
			auto iterToErase = iter++;
			if (iter == list.end()) {
				iter = list.begin();
			}
			list.erase(iterToErase);
			if (list.size() == 2)
				break;
			for (int j = 1; j < numNext; j++)
			{
				++iter;
				if (iter == list.end()) {
					iter = list.begin();
				}
			}
		}

		for (auto iter = list.begin(); iter != list.end(); ++iter) {
			cout << *iter << ' ';
		}
		cout << nextl;

	}

	return 0;
}