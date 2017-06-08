#include <iostream>
#include <string>
#include <vector>

#define FOR(i,n) for(int i = 0 ; i < n; i++)

using namespace std;

const int dx[8] = { -1, -1, -1, 1, 1, 1, 0, 0 };
const int dy[8] = { -1, 0, 1, -1, 0, 1, -1, 1 };
char board[5][6];
vector<bool> isCheck(26);
bool solBoard[26][5][5];

void makeSolBoard(char letter)
{
	FOR(i, 5)
		FOR(j, 5)
	{
		if (board[i][j] == letter)
			solBoard[letter - 'A'][i][j] = true;
	}
	isCheck[letter - 'A'] = true;
}

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
		isCheck.clear();

		FOR(i, numWord)
		{
			bool verdict = false;
			string wordToCheck;
			cin >> wordToCheck;

			bool possibleToWord[5][5];
			int numPossibleToWord = 25;
			for (int x = 0; x < 5; x++)
			{
				for (int y = 0; y < 5; y++)
				{
					possibleToWord[y][x] = 1;
				}
			}

			for (int idxCheck = 0; idxCheck < wordToCheck.size() ; idxCheck++)
			{
				if (isCheck[wordToCheck.at(idxCheck) - 'A'] == false)
				{
					makeSolBoard(wordToCheck.at(idxCheck));
				}

				

				if (numPossibleToWord == 0)
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