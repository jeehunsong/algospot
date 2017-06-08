#include <iostream>
#include <string>
#include <vector>

#define FOR(i,n)	for(int i = 0 ; i < n ; i++)

using namespace std;

int numWord;
vector<string> word;

vector<vector<int>> cacheOverlap;
vector<vector<int>> cache;
vector<int> contain;

#define VECTORELENGTH 16

int overlap(int last, int next)
{
	int &ret = cacheOverlap[last][next];
	ret = 0;

	if (last == next)
	{
		ret = word[last].length();
		return ret;
	}

	//next가 last에게 포함됨
	if ((word[last].find(word[next]) != string::npos) && (word[last].length() > word[next].length())) {
		contain[next] = 1;
		return ret;
	}

	for (int testLength = 1; testLength <= 20; testLength++) {
		if (testLength > word[last].length() || testLength > word[next].length())
			break;

		string lastWord = word[last].substr(word[last].length() - testLength, testLength);
		string nextWord = word[next].substr(0, testLength);

		if (lastWord == nextWord)
			ret = testLength;
	}

	return ret;
}

// 리턴값: 최대 겹친 글자 수
// taken: 지금까지 사용한 단어
// prev: 직전 단어. -1이면 직전 단어 없음.
int restore(int last, int taken)
{
	if (taken == (1 << numWord - 1))
		return 0;
	
	int & ret = cache[last][taken];
	if (ret != -1)
		return ret;
	ret = 0;

	for (int next = 0; next < numWord; next++)
	{
		if ((taken & (1 << next)) || (contain[next] == 1))
			continue;

		int nextTaken = taken | (1 << next);
		int temp = cacheOverlap[last][next] + restore(next, (nextTaken));
		if (temp > ret)
			ret = temp;
	}
	return ret;
}

string reconstruct(int last, int used) {
	// 끝까지 순회
	if (used == (1 << numWord) - 1) return "";
	for (int next = 0; next < numWord; next++)
	{
		if (used & (1 << next) || (contain[next] == 1))
			continue;

		int temp = restore(next, used | (1 << next)) + cacheOverlap[last][next];
		if (restore(last, used) == temp) {
			return (word[next].substr(cacheOverlap[last][next]) + reconstruct(next, used + (1 << next)));
		}
	}
	return "";
}

int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	while (cases--)
	{
		cin >> numWord;
		
		word.clear();
		FOR(i, numWord) {
			string temp;
			cin >> temp;
			word.push_back(temp);
		}

		cacheOverlap.clear();
		cacheOverlap.resize(VECTORELENGTH, vector<int>(VECTORELENGTH, 0));
		contain.clear();
		contain.resize(VECTORELENGTH, 0);
		cache.clear();
		cache.resize(VECTORELENGTH, vector<int>(1 << VECTORELENGTH, -1));

		FOR(i, numWord)
			FOR(j, numWord) {
			overlap(i, j);
		}
		
		int maxOverlap = -1;
		int maxStart = -1;
		for (int i = 0; i < numWord; i++)
		{
			if (contain[i] == 0) {
				int temp = restore(i, (1<<i));
				if (temp > maxOverlap) {
					maxOverlap = temp;
					maxStart = i;
				}
			}
		}
		cout << (word[maxStart] + reconstruct(maxStart, 1 << maxStart)) << '\n';
	}
	return 0;
}