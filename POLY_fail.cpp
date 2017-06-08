#include <iostream>
#include <string>
#include <vector>

using namespace std;

//#define DEBUG
#define MAXN	100
#define MODULO	10000000

vector<vector<unsigned int>> solution(MAXN + 1);
vector<unsigned int> sum(MAXN + 1, 0);

void solveForN(int idxN)
{
	solution[idxN].resize(idxN + 1);
	
	for (int numTop = 1 ; numTop < idxN; numTop++)
	{
		solution[idxN][numTop] = 0;
		for (int numSecond = 1 ; numSecond <= (idxN - numTop) ; numSecond++)
		{
			solution[idxN][numTop] = (solution[idxN][numTop] +(numTop + numSecond - 1) * solution[idxN - numTop][numSecond]) % MODULO;
		}

#ifdef DEBUG
		cout << solution[idxN][numTop] << " ";
#endif // DEBUG

		sum[idxN] = (sum[idxN] + solution[idxN][numTop]) % MODULO;
	}

	solution[idxN][idxN] = 1;
	sum[idxN] = (sum[idxN] + 1) % MODULO;
#ifdef DEBUG
	cout << solution[idxN][idxN] << " Total: " << sum[idxN] << endl;
#endif // DEBUG
}


int main()
{
	//init
	int	numAlreadySolved = 2;
	solution[1].resize(1 + 1);
	solution[1][1] = 1;
	solution[2].resize(2 + 1);
	solution[2][1] = 1;
	solution[2][2] = 1;
	sum[1] = 1;
	sum[2] = 2;

	int cases;
	cin >> cases;

	while (cases--)
	{
		int wellDepth;
		cin >> wellDepth;

#ifdef DEBUG
		cout << "#: " << n << endl;
#endif // DEBUG

		for (int idxN = numAlreadySolved + 1 ; idxN <= wellDepth; idxN++)
		{
#ifdef DEBUG
			cout << "Calculate for " << idxN << endl;
#endif // DEBUG

			solveForN(idxN);
		}

		cout << sum[wellDepth] << endl;
	}
	return 0;
}