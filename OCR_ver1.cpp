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
//vector<vector<double>> cache;

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

	cin.sync_with_stdio(false);
	cin >> m >> q;

	//cache.resize(102, vector<double>(502, 2.0));
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
		//cin >> B[idxWords];
		scanf(" %lf", &B[idxWords]);
		B[idxWords] = max(log(B[idxWords]), MINUSINFINITY);
	}

	
	FOR(i, m)
		FOR(j, m)
	{
		//cin >> input;//T[i][j];
		scanf("%lf ", &input);
		//T[i][j] = max(log(T[i][j]), MINUSINFINITY);
		T[i][j] = max(log(input), MINUSINFINITY);
	}
	

	FOR(i, m)
		FOR(j, m)
	{
		//cin >> M[i][j];
		//M[i][j] = max(log(M[i][j]), MINUSINFINITY);
		//cin >> input;
		scanf("%lf ", &input);
		M[i][j] = max(log(input), MINUSINFINITY);
	}

	FOR(idxSentences, q)
	{
		string testSentence;

		//cin.clear();
		//cin.ignore(256, ' ');
		//cin >> n;
		scanf("%d ", &n);

		//printf("(%d)Input words: ", n);
		FOR(idxTest, n)
		{
			cin.clear();
			//cin.ignore(256, ' ');
			cin >> testSentence;
			R[idxTest] = dictionary[testSentence];
			//cout << R[idxTest] << ' ';
		}
		//cout << '\n';

		double maxProb = -1e200;
		int maxFirst;
		//첫번째 단어
		FOR(idxFirst, m)
		{
			double tempProb = B[idxFirst] + M[R[0]][idxFirst];
			//printf("First %d probability %1.5lf ==> ", idxFirst, tempProb);
			tempProb += recognize(1, idxFirst);;
			//printf("%1.5lf\n", tempProb);
			
			if (tempProb > maxProb)
			{
				maxProb = tempProb;
				maxFirst = idxFirst;
			}
		}

		cout << reconstruct(0, maxFirst) << '\n';
	}



	return 0;
}