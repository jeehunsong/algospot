#include <iostream>
#include <string>
#include <vector>
#include <map>

#define FOR(i,n)	for(int i = 0 ; i < n ; i++)

using namespace std;

vector<string> words;
vector<double> probFirst;
vector<vector<double>> probCollo;
vector<vector<double>> probConfuse;

vector<int> testIdx;
vector<int> resultIdx;
int testNum;

vector<vector<double>> cache;
vector<vector<int>> choice;

double checkProbability(int curPos, int preWord)
{
	//printf("curPos %d preWord %d\n", curPos, preWord);
	if (curPos == testIdx.size())
	{
		return 1.0;
	}

	double & ret = cache[curPos][preWord];

	if (ret > -0.5)
	{
		return ret;
	}

	ret = 0.0;
	if (curPos == 0)
	{
		for (int i = 0; i < words.size(); i++)
		{
			//tempProb는 시작을 i인데 testIdx[0]로 혼동한 확률 * 그 이후의 경우
			double tempProb = checkProbability(curPos + 1, i) * probFirst[i] * probConfuse[testIdx[curPos]][i];

			if (ret < tempProb)
			{
				ret = tempProb;
				resultIdx[0] = i;
			}
		}
		cout << resultIdx[0] << endl;
	}
	else
	{
		for (int i = 0; i < words.size(); i++)
		{
			//tempProb는 시작을 i인데 testIdx[0]로 혼동한 확률 * 그 이후의 경우
			double tempProb = checkProbability(curPos + 1, i) * probCollo[testIdx[curPos - 1]][testIdx[curPos]] * probConfuse[testIdx[curPos]][i];

			if (ret < tempProb)
			{
				ret = tempProb;
				choice[curPos][preWord];
			}
		}
	}

	return ret;
}

void reconstruct()
{
	
	for (int i = 1; i < testNum ; i++)
	{
		cout << '.';
		resultIdx[i] = choice[i][resultIdx[i - 1]];
		cout << resultIdx[i];
	}

}

int main()
{
	int numWords, numSentences;
	map<string, int> dictionary;

	cin.sync_with_stdio(false);
	cin >> numWords >> numSentences;

	words.resize(numWords);
	FOR(idxWords, numWords)
	{
		cin >> words[idxWords];
		dictionary.insert(make_pair(words[idxWords], idxWords));
	}

	probFirst.resize(numWords);
	FOR(idxWords, numWords)
	{
		cin >> probFirst[idxWords];
	}

	probCollo.resize(numWords, vector<double>(numWords));
	FOR(i, numWords)
		FOR(j, numWords)
	{
		cin >> probCollo[i][j];
	}

	probConfuse.resize(numWords, vector<double>(numWords));
	FOR(i, numWords)
		FOR(j, numWords)
	{
		cin >> probConfuse[i][j];
	}
	
	FOR(idxSentences, numSentences)
	{
		vector<string> testSentence;

		cin >> testNum;
		testSentence.resize(testNum);
		testSentence.clear();
		testIdx.clear();
		resultIdx.clear();
		resultIdx.resize(testNum);
		cache.clear();
		cache.resize(100, vector<double>(500, -1));
		choice.clear();
		choice.resize(100, vector<int>(100, -1));

		FOR(idxTest, testNum)
		{
			cin >> testSentence[idxTest];
			testIdx.push_back(dictionary[testSentence[idxTest]]);
		}

		cout << checkProbability(0, 0) << endl;

		reconstruct();

		
	}



	return 0;
}