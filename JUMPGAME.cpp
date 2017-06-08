#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>

#define FOR(i,n) for(int i = 0 ; i < n; i++)

using namespace std;

int grid[100][100];
int cache[100][100];
int gridSize;

bool jump_exhaustive(int y, int x)
{
	if ((y >= gridSize) || (x >= gridSize))
	{
		return false;
	}
	if ((y == gridSize - 1 ) && (x == gridSize - 1))
	{
		return true;
	}
	return jump_exhaustive(y + grid[y][x], x) || jump_exhaustive(y, x + grid[y][x]);
}

int jump_memoization(int y, int x)
{
	if ((y >= gridSize) || (x >= gridSize))
	{
		return 0;
	}
	if ((y == gridSize - 1) && (x == gridSize - 1))
	{
		return 1;
	}
	int & ret = cache[y][x];
	if (ret != -1)
	{
		return ret;
	}
	//책에서 언급 안 된 부분.
	cache[y][x] = jump_memoization(y + grid[y][x], x) || jump_memoization(y, x + grid[y][x]);
	return cache[y][x];
}

int main()
{
	int cases;
	cin >> cases;
	while (cases--)
	{
		cin >> gridSize;
		bool ret;

		memset(grid, 0, sizeof(grid));
		memset(cache, -1, sizeof(cache));
		
		FOR(i, gridSize)
			FOR(j, gridSize)
		{
			//cin >> grid[i][j];
			scanf("%d", &grid[i][j]);
		}
		
		ret = jump_memoization(0, 0);
		//ret = jump_exhaustive(0, 0);
		if (ret == true)
		{
			cout << "YES" << endl;
		}
		else
		{
			cout << "NO" << endl;
		}
	}
	return 0;
}