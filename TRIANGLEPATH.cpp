#include <iostream>
#include <string.h>

#define FOR(i,n) for(int i = 0 ; i < n; i++)
#define MAX(x, y)	((x) > (y) ? (x) : (y))

using namespace std;

int sizeTriangle;
int triangle[100][100];
int cache[100];

int pathExhaustive(int row, int col, int max)
{
	max += triangle[row][col];
	if (row == (sizeTriangle - 1))
	{
		return max;
	}
	return MAX(pathExhaustive(row + 1, col, max), pathExhaustive(row + 1, col + 1, max));
}

int pathMyReverseWay()
{
	for (int i = 0; i < sizeTriangle; i++)
	{
		cache[i] = triangle[sizeTriangle - 1][i];
	}

	for (int idxRow = sizeTriangle - 2 ; idxRow >= 0 ; idxRow--)
	{
		for (int idxCol = 0; idxCol <= idxRow; idxCol++)
		{
			cache[idxCol] = triangle[idxRow][idxCol] + MAX(cache[idxCol], cache[idxCol + 1]);
		}
	}
	return cache[0];
}


int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	while (cases--)
	{
		cin >> sizeTriangle;
		memset(triangle, -1, sizeof(triangle));

		FOR(idxRow, sizeTriangle)
			FOR(idxCol, idxRow + 1)
		{
			cin >> triangle[idxRow][idxCol];
		}

		//int maxSum = pathExhaustive(0, 0, 0);
		int maxSum = pathMyReverseWay();

		cout << maxSum << '\n';
	}
	return 0;
}