#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string.h>
#include <math.h>

using namespace std;

#define FOR(i,n)	for(int i = 0 ; i < n ; i++)

#define MINUSINFINITY		-1e200

inline double max(double a, double b)
{
	return (a > b) ? (a) : (b);
}

int n, m, q;
int R[100];
double B[501], T[501][501];
double M[501][501];
int choice[102][502];
double cache[102][502];

double recognize(int segment, int previousMatch)
{
	if (segment == n) return 0;
	double & ret = cache[segment][previousMatch];
	if (ret < 1.0) return ret;
	ret = -1e200;
	int & choose = choice[segment][previousMatch];
	for (int thisMatch = 0; thisMatch < m; thisMatch++)
	{
		double cand = T[previousMatch][thisMatch]
			+ M[thisMatch][R[segment]]
			+ recognize(segment + 1, thisMatch);
		if (ret < cand)
		{
			ret = cand;
			choose = thisMatch;
		}
	}
	return ret;
}

string corpus[501];
string reconstruct(int segment, int previousMatch)
{
	int choose = choice[segment][previousMatch];
	string ret = corpus[choose];
	if (segment < n - 1)
	{
		ret = ret + " " + reconstruct(segment + 1, choose);
	}
	return ret;
}

int main()
{
	map<string, int> dictionary;
	double input;
	string testSentence;

	cin.sync_with_stdio(false);
	cin >> m >> q;

	FOR(i, 102)
		FOR(j, 502)
			cache[i][j] = 2.0;

	FOR(idxWords, m)
	{
		cin >> corpus[idxWords];
		dictionary.insert(make_pair(corpus[idxWords], idxWords));
	}

	FOR(idxWords, m)
	{
		scanf(" %lf", &B[idxWords]);
		//B[idxWords] = max(log(B[idxWords]), MINUSINFINITY);
		B[idxWords] = (log(B[idxWords]));
	}


	FOR(i, m)
		FOR(j, m)
	{
		scanf("%lf ", &input);
		//T[i][j] = max(log(input), MINUSINFINITY);
		T[i][j] = (log(input));
	}


	FOR(i, m)
		FOR(j, m)
	{
		scanf("%lf ", &input);
		//M[i][j] = max(log(input), MINUSINFINITY);
		M[i][j] = log(input);
	}

	FOR(idxSentences, q)
	{
		scanf("%d ", &n);
		memset(cache, -1, sizeof(cache));

		FOR(idxTest, n)
		{
			cin.clear();
			testSentence.clear();
			cin >> testSentence;
			R[idxTest] = dictionary[testSentence];
		}

		double maxProb = -1e200;
		int maxFirst = -1;

		FOR(idxFirst, m)
		{
			double tempProb = B[idxFirst] + M[R[0]][idxFirst];
			tempProb += recognize(1, idxFirst);;

			if (tempProb > maxProb)
			{
				maxProb = tempProb;
				maxFirst = idxFirst;
			}
		}

		if (maxFirst != -1)
			cout << reconstruct(0, maxFirst) << '\n';
		else
			cout << "SOMETHING WRONG!!!" << '\n';
	}
	return 0;
}