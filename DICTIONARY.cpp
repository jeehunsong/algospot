#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

#define	INVALID	"INVALID HYPOTHESIS"

int numWord;
vector<string> words;

int adj[26][26];	//[prev] 다음 [cur] 가 온다.
vector<bool> visited;
vector<int> dic;

void makeAdj()
{
	memset(adj, 0, sizeof(adj));

	for (int i = 1; i < words.size(); i++) {
		string& prev = words[i - 1];
		string& cur = words[i];
		int length = min(prev.length(), cur.length());

		for (int iChar = 0; iChar < length; iChar++) {
			// 처음으로 글자가 다르다
			if (prev[iChar] != cur[iChar]) {
				adj[prev[iChar] - 'a'][cur[iChar] - 'a'] = 1;
				//cout << prev[iChar] << " " << cur[iChar] << nextl;
				break;
			}
		}
	}
}

void dfs(int head) {
	visited[head] = true;
	for (int i = 0; i < 26; i++)
	{
		if (adj[head][i] == 1 && visited[i] == false)
		{
			dfs(i);
		}
	}
	dic.push_back(head);
}

void dfsAll()
{
	visited = vector<bool>(26, false);
	dic.clear();
	for (int i = 0; i < 26; i++)
	{
		if (visited[i] == false)
		{
			dfs(i);
		}
	}
}

void solve()
{
	for (int i = 0; i < 26; i++)
	{
		int prev = dic[i];
		for (int j = i + 1; j < 26; j++)
		{
			int cur = dic[j];
			// 사전 뒤에서 앞으로 가는 길이 있다.
			if (adj[prev][cur] == 1)
			{
				cout << INVALID << nextl;
				//cout << char(prev + 'a') << ' ' << char(cur + 'a') << nextl << nextl;
				return;
			}
		}
	}
	for (int i = 0; i < 26; i++)
	{
		cout << char(dic[25 - i] + 'a');
	}
	cout << nextl;
}

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;


	while (numCase--)
	{
		cin >> numWord;
		words.clear();
		for (int i = 0; i < numWord; i++)
		{
			string temp;
			cin >> temp;
			words.push_back(temp);
		}
		
		makeAdj();

		dfsAll();

		solve();
	}

	return 0;
}