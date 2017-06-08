#include <iostream>
#include <vector>

#define FOR(i,n)	for(int i = 0 ; i < n ; i++)

using namespace std;

vector<vector<int>> adjacency;
vector<vector<double>> prob;
vector<int> numConn;
int prison;
int numTown;

double search3(int here, int days)
{
	if (days ==0)
	{
		return (here == prison ? 1.0 : 0.0);
	}
	double & ret = prob[here][days];
	if (ret > -0.5) return ret;
	ret = 0.0;
	for (int there = 0; there < numTown; there++)
	{
		if (adjacency[here][there])
		{
			ret += search3(there, days - 1) / numConn[there];
		}
	}
	return ret;
}

int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	while (cases--)
	{
		int days;

		cin >> numTown >> days >> prison;

		adjacency.clear();
		adjacency.resize(numTown, vector<int>(numTown));
		prob.clear();

		prob.resize(numTown, vector<double>(numTown, -1.0));
		
		numConn.clear();
		numConn.resize(numTown, 0);

		FOR(i, numTown)
			FOR(j, numTown)
		{
			cin >> adjacency[i][j];
			numConn[i] += adjacency[i][j];
		}

		int numQuestion;
		cin >> numQuestion;
		FOR(I, numQuestion)
		{
			int town;
			cin >> town;

			printf("%.10lf ", search3(town, days));
		}
		cout << '\n';
	}
	return 0;
}