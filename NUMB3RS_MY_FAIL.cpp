#include <iostream>
#include <vector>

#define FOR(i,n)	for(int i = 0 ; i < n ; i++)

using namespace std;


int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	while (cases--)
	{
		int numTown, days, prison;

		cin >> numTown >> days >> prison;

		vector<vector<int>> adjacency(numTown, vector<int>(numTown));
		vector<double> prob(numTown, 0.0);
		vector<int> numConn(numTown, 0);
		prob[prison] = 1.0;

		FOR(i, numTown)
			FOR(j, numTown)
			{
				cin >> adjacency[i][j];
				numConn[i] += adjacency[i][j];
			}

		for (int idxDay = 0; idxDay < days; idxDay++)
		{
			vector<double> tempProb = prob;

			prob.clear();
			prob.resize(numTown, 0.0);
			for (int srcTown = 0; srcTown < numTown; srcTown++)
			{
				for (int dstTown = 0; dstTown < numTown; dstTown++)
				{
					if (adjacency[srcTown][dstTown] == 1)
					{
						prob[dstTown] += tempProb[srcTown] / numConn[srcTown];
					}
				}
			}

		}

		int numQuestion;
		cin >> numQuestion;
		FOR(I, numQuestion)
		{
			int town;
			cin >> town;

			printf("%.8lf ", prob[town]);
		}
		cout << '\n';
	}
	return 0;
}