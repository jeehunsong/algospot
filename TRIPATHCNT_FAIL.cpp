#include <iostream>
#include <string.h>

#define FOR(i,n) for(int i = 0 ; i < n; i++)

using namespace std;
int sizeTriangle;
int triangle[100][100];
int path[100][101];
int countCache[100][100];

inline max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}

int path2(int x, int y)
{
	if (y == sizeTriangle - 1)
	{
		return triangle[y][x];
	}
	int & ret = countCache[y][x];
	if (ret != -1)
	{
		return ret;
	}

	return ret = max(path2(y + 1, x), path2(y + 1, x + 1)) + triangle[y][x];
}

int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	while (cases--)
	{
		cin >> sizeTriangle;

		for (int i = 0; i < sizeTriangle; i++)
		{
			for (int j = 0; j < sizeTriangle ; j++)
			{
				cin >> triangle[i][j];
			}
		}
		
		memset(path, -1, sizeof(path));
		memset(countCache, -1, sizeof(countCache));


	}
	return 0;
}