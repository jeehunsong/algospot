#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

enum {
	eBlocked = 0,
	eAvailable = 1,
};

int gHeight, gWidth, gRow, gCol;
vector<vector<int>> board, tile[4], boardAlreadyVisited[4];
int gBoardAvailable = 0, gTileBlockNum = 0, gRot;

bool check(int row, int col, int rotation)
{
	int localRow, localCol;

	if (rotation % 2 == 0) {
		if ((gHeight < (gRow + row)) || (gWidth < (gCol + col)))
			return false;
		localRow = gRow;
		localCol = gCol;
	}
	else {
		if ((gHeight < (gCol + row)) || (gWidth < (gRow + col)))
			return false;
		localRow = gCol;
		localCol = gRow;
	}

	for (int i = 0; i < localRow; i++)
	{
		for (int j = 0; j < localCol; j++)
		{
			// Both blocked: Not available
			if (((tile[rotation][i][j] == eBlocked) && (board[i + row][j + col] == eBlocked))) {
				return false;
			}
			// Else: OK
		}
	}

	return true;
}

void putTile(int row, int col, int rotation)
{
	int localRow, localCol;

	if (rotation % 2 == 0) {
		localRow = gRow;
		localCol = gCol;
	}
	else {
		localRow = gCol;
		localCol = gRow;
	}

	for (int i = 0; i < localRow; i++)
	{
		for (int j = 0; j < localCol; j++)
		{
			if (tile[rotation][i][j] == eBlocked)
			{
				if (board[i + row][j + col] == eAvailable) {
					board[i + row][j + col] = eBlocked;
					--gBoardAvailable;
				}
				else
					assert(false);
			}
		}
	}

	//printf("Put block on (%d, %d), now %d available\n", row, col, gBoardAvailable);
}

void removeTile(int row, int col, int rotation)
{
	int localRow, localCol;

	if (rotation % 2 == 0) {
		localRow = gRow;
		localCol = gCol;
	}
	else {
		localRow = gCol;
		localCol = gRow;
	}

	for (int i = 0; i < localRow; i++)
	{
		for (int j = 0; j < localCol; j++)
		{
			if (tile[rotation][i][j] == eBlocked)
			{
				if (board[i + row][j + col] == eBlocked) {
					board[i + row][j + col] = eAvailable;
					++gBoardAvailable;
				}
				else
					assert(false);
			}
		}
	}

	//printf("Remove block on (%d, %d), now %d available\n", row, col, gBoardAvailable);
}

void printBoard(int cycle)
{
#if 0
	//if (cycle == 0)
	{
		cout << "Print Board " << cycle << nextl;
		for (int i = 0; i < gHeight; i++) {
			for (int j = 0; j < gWidth; j++)
			{
				char c = board[i][j] == eAvailable ? '.' : '#';
				cout << c;
			}
			cout << nextl;
		}
		cout << nextl;
	}
#endif
}

void printTile()
{
	
	for (int k = 0; k < gRot; k++)
	{
		cout << "Print Tile " << k << nextl;
		for (int i = 0; i < tile[k].size(); i++) {
			for (int j = 0; j < tile[k][0].size(); j++)
			{
				char c = tile[k][i][j] == eAvailable ? '.' : '#';
				cout << c;
			}
			cout << nextl;
		}
		cout << nextl;
	}
}

int callCnt = 0;

int exhaustive(int cycle, int count, int row, int col, int rot)
{
	int retVal = 0;

	//printf("Call number %d (%d, %d, %d) cycle %d\n", count, row, col, rot, cycle);

	printBoard(cycle);

	for (int idxRow = 0; idxRow < gHeight; idxRow++)
	{
		for (int idxCol = 0; idxCol < gWidth; idxCol++)
		{
			for (int idxRotation = 0; idxRotation < gRot; idxRotation++)
			{
				//printf("Check (%d, %d, %d), cycle %d\n", idxRow, idxCol, idxRotation, cycle);
				if ((check(idxRow, idxCol, idxRotation) == true) && (boardAlreadyVisited[idxRotation][idxRow][idxCol] == eAvailable))
				{
					//if(cycle == 0)
#if 0
					for (int i = 0; i < cycle; i++)
						cout << ' ';
#endif
					//printf("(%d, %d, %d) success, cycle %d, retVal %d\n", idxRow, idxCol, idxRotation, cycle, retVal);

					// 벽돌을 놓는다.
					putTile(idxRow, idxCol, idxRotation);
					printBoard(cycle);

					if ((gBoardAvailable / gTileBlockNum + 1) > retVal)
					{
						retVal = MAX(retVal, 1 + exhaustive(cycle + 1, callCnt++, idxRow, idxCol, idxRotation));
					}

					//printf("(%d, %d, %d) end of putTile, cycle %d, retVal %d\n", idxRow, idxCol, idxRotation, cycle, retVal);

					// 벽돌을 제거한다.
					removeTile(idxRow, idxCol, idxRotation);
					printBoard(cycle);

					// 무한 루프를 방지하기 위해, 현재 위치를 막는다.
					// 왼쪽 위에서부터 진행하므로 이 연산은 뒤에 영향을 주지 않는다.
					boardAlreadyVisited[idxRotation][idxRow][idxCol] = eBlocked;
					
					if ((gBoardAvailable / gTileBlockNum + 1) > retVal)
					{
						retVal = MAX(retVal, exhaustive(cycle + 1, callCnt++, idxRow, idxCol, idxRotation));
						//board[idxRow][idxCol] = eAvailable;
					}

					boardAlreadyVisited[idxRotation][idxRow][idxCol] = eAvailable;
					//printf("(%d, %d, %d) end of removeTile, cycle %d, retVal %d\n", idxRow, idxCol, idxRotation, cycle, retVal);

					//cout << "Retn number " << count << " Ret " << retVal << " cycle " << cycle << nextl;

					return retVal;
				}
			}
		}
	}

	//if (cycle == 0)
	
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
		board.clear();
		board.resize(gHeight, vector<int>(gWidth, 0));
		for (int i = 0; i < 4; i++) {
			boardAlreadyVisited[i].clear();
			boardAlreadyVisited[i].resize(gHeight, vector<int>(gWidth, eAvailable));
			tile[i].clear();
			if (i % 2 == 0)
			{
				tile[i].resize(gRow, vector<int>(gCol, 0));
			}
			else
			{
				tile[i].resize(gCol, vector<int>(gRow, 0));
			}
		}

		printf("gHeight %d gWidth %d gRow %d gCol %d\n", gHeight, gWidth, gRow, gCol);

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
				{
					tile[0][i][j] = eAvailable;
					tile[1][j][gRow - i - 1] = eAvailable;
					tile[2][gRow - i - 1][gCol - j - 1] = eAvailable;
					tile[3][gCol - j - 1][i] = eAvailable;
				}
				else
					gTileBlockNum++;
			}
		}

		gRot = 2;
		for (int i = 0; i < gRow; i++)
		{
			for (int j = 0; j < gCol; j++)
			{
				if (tile[0][i][j] != tile[2][i][j])
				{
					gRot = 4;
					break;
				}
			}
			if (gRot != 2)
				break;
		}

		cout << nextl;
		printTile();

		printf("Board %d tile %d\n", gBoardAvailable, gTileBlockNum);

		cout << exhaustive(0, callCnt++, -1, -1, -1) << nextl;
	}

	return 0;
}