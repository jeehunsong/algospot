#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main()
{
	int cases;
	cin >> cases;
	while (cases--)
	{
		int N, L;
		int temp = 0;
		double sol;

		cin >> N >> L;
		vector<int> cost(N + 1, 0);

		for (int idxDay = 1; idxDay <= N; idxDay++)
		{
			cin >> temp;
			cost[idxDay] = cost[idxDay - 1] + temp;
			//cout << cost[idxDay] << endl;
		}

		sol = (double)cost[N] / (double)L;
		//printf("cost[%d] to cost[%d]: %d\n", 1, L, cost[L] - cost[1 - 1]);

		for (int idxStart = 1; idxStart <= (N - L + 1); idxStart++)
		{
			for (int idxEnd = (idxStart + L - 1); idxEnd <= N; idxEnd++)
			{
				//printf("cost[%d] to cost[%d]: %d\n", idxStart, idxEnd, cost[idxEnd] - cost[idxStart - 1]);
				if ((double)(cost[idxEnd] - cost[idxStart - 1]) / (double)(idxEnd - idxStart + 1) < sol)
				{
					sol = (double)(cost[idxEnd] - cost[idxStart - 1]) / (double)(idxEnd - idxStart + 1);
				}
			}
		}

		printf("%.12lf\n", sol);
	}
	return 0;
}