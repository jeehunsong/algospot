#include <iostream>
#include <vector>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

enum {
	eBlocked = 0,
	eAvailable = 1,
};

int gHeight, gWidth, gRow, gCol;
vector<vector<int>> board, tile;
int gBoardAvailable = 0, gTileBlockNum = 0;

bool check(vector<vector<int>> board, vector<vector<int>> tile, int rotation, int row, int col)
{
	int localRow, localCol;
	vector<vector<int>> tileRotated;

	if (rotation % 2 == 0)	{
		if ((gHeight < (gRow + row)) || (gWidth < (gCol + col)))
			return false;
		localRow = gRow;
		localCol = gCol;
	}
	else {
		if ((gHeight < (gCol + row)) || (gWidth < (gRow + col)))
			return false;
		tileRotated.resize(gCol, vector<int>(gRow, 0));
		localRow = gCol;
		localCol = gRow;
	}

	
	if (rotation == 0)	{
		tileRotated = tile;
	}
	else if (rotation == 1)	{
		for (int i = 0; i < gRow; i++)
		{
			for (int j = 0; j < gCol; j++)
			{
				tileRotated[j][localCol - i - 1] = tile[i][j];
			}
		}
	}
	else if (rotation == 2)	{
		tileRotated.resize(gRow, vector<int>(gCol, 0));
		for (int i = 0; i < gRow; i++)
		{
			for (int j = 0; j < gCol; j++)
			{
				tileRotated[gRow - i - 1][gCol - j - 1] = tile[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < gRow; i++)
		{
			for (int j = 0; j < gCol; j++)
			{
				tileRotated[gCol - j - 1][i] = tile[i][j];
			}
		}
	}
	
	for (int i = 0; i < localRow; i++)
	{
		for (int j = 0; j < localCol; j++)
		{
			//printf("(%d, %d) in (%d, %d) /  (%d, %d) in (%d, %d)\n", i, j, tileRotated.size(), tileRotated[0].size(), i + row, j + col, board.size(), board[0].size());
			if (((tileRotated[i][j] == eBlocked) && (board[i + row][j + col] == eBlocked))) {
				return false;
			}
		}
	}

	return true;
}

int exhuastive(vector<vector<int>> board)
{
	int retVal = 0;
	
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < gHeight; i++)
		{
			for (int j = 0; j < gWidth; j++)
			{
				cout << check(board, tile, k, i, j);
			}
			cout << nextl;
		}
		cout << nextl << nextl;
	}
	return retVal;
}

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;

	while (numCase--)
	{
		cin >> gHeight >> gWidth >> gRow >> gCol;
		board.resize(gHeight, vector<int>(gWidth, 0));
		tile.resize(gRow, vector<int>(gCol, 0));

		for (int i = 0; i < gHeight; i++)
		{
			for (int j = 0; j < gWidth; j++)
			{
				char temp;
				cin >> temp;
				if (temp == '.') {
					board[i][j] = eAvailable;
					gBoardAvailable++;
				}
			}
		}
		
		for (int i = 0; i < gRow; i++)
		{
			for (int j = 0; j < gCol; j++)
			{
				char temp;
				cin >> temp;
				if (temp == '.')
					tile[i][j] = eAvailable;
				else
					gTileBlockNum++;
			}
		}

		exhuastive(board);
	}

	return 0;
}