#include <iostream>
#include <string>

#define FOR(i,n) for(int i = 0 ; i < n; i++)

using namespace std;

const int dx[8] = { -1, -1, -1, 1, 1, 1, 0, 0 };
const int dy[8] = { -1, 0, 1, -1, 0, 1, -1, 1 };
char board[5][6];

bool inRange(int y, int x)
{
	if ((y < 5) && (y >= 0) && (x < 5) && (x >= 0))
	{
		return true;
	}
	return false;
}

bool hasWord(int y, int x, const string& word) 
{
	if (!inRange(y, x))
	{
		return false;
	}
	if (board[y][x] != word[0])
	{
		return false;
	}
	if (word.size() == 1)
	{
		return true;
	}
	for (int direction = 0; direction < 8; direction++)
	{
		int nextY = y + dy[direction], nextX = x + dx[direction];
		if (hasWord(nextY, nextX, word.substr(1)))
		{
			return true;
		}
	}
	return false;
}

int main()
{
	int cases;
	cin >> cases;

	while (cases--)
	{
		for (int y = 0; y < 5; y++)
		{
			cin >> board[y];
		}

		int numWord;
		cin.ignore();
		cin >> numWord;

		FOR(i, numWord)
		{
			bool verdict = false;
			string wordToCheck;
			cin >> wordToCheck;

			FOR(x, 5)
			{
				FOR(y, 5)
				{
					verdict = hasWord(x, y, wordToCheck);
					if (verdict)
					{
						break;
					}
				}
				if (verdict)
				{
					break;
				}
			}

			cout << wordToCheck << " ";
			if (verdict)
			{
				cout << "YES" << endl;
			}
			else
			{
				cout << "NO" << endl;
			}
		}
	}
	return 0;
}