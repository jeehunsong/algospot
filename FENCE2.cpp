#include <iostream>
#include <string>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

int numFence;
int height[20000], left[20000], right[20000];

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

		cin >> numFence;
		for (int i = 0; i < numFence; i++)
		{
			cin >> height[i];

		}

	}

	return 0;
}