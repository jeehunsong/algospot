// 초안은 직접 작성했음
// 디버깅은 책 내용 참조.


#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

#define nextl '\n'

vector<string> dic;
vector<int> visited;
int numWord;

// vertex: 알파벳
// edge: 단어
vector<vector<int>> adj;
vector<string> adjString[26][26];
int inflow[26], outflow[26];


void dfs(int head) {
	for (int i = 0; i < 26; i++)
	{
		while (adj[head][i] > 0) {
			adj[head][i]--;
			dfs(i);
		}
	}
	visited.push_back(head);
	// 가장 치명적인 디버깅 내용. 내가 짠 코드는 edge를 넣었는데, 그러지 말고 문자만 넣고 나중에 edge를 꺼내면 된다.
}

bool dfsAll(int start) 
{
	visited.clear();

	// 주어진 점 스타트
	if (start != -1)
		dfs(start);
	// 임의의 점 스타트
	else {
		for (int i = 0; i < 26; i++)
		{
			if (inflow[i] != 0) {
				dfs(i);
				break;
			}
		}
	}

	bool retVal = (dic.size() + 1 == visited.size());
	
	return retVal;
}

void solve() {
	// alphabet을 순회하면서 start-end를 정할 수 있는지 본다.
	bool isValid = true;
	int start = -1, end = -1;

	for (int i = 0; i < 26; i++)
	{
		//시작점인가?
		if (inflow[i] - outflow[i] == 1) {
			if (start == -1) start = i;
			else {
				isValid = false;
				break;
			}
		}
		//끝점인가?
		else if (inflow[i] - outflow[i] == -1) {
			if (end == -1) end = i;
			else {
				isValid = false;
				break;
			}
		}
		else if (inflow[i] != outflow[i]) {
			isValid = false;
			break;
		}
		// 같은 경우는 OK
	}

	// 시작점/끝점에 의해 invliad 한 경우 리턴
	if ((isValid == false) || (start == -1 && end != -1) ||	(start != -1 && end == -1)) 
	{
		isValid = false;
	}
	// 시작점, 끝점이 특정된 경우
	else
	{
		isValid = dfsAll(start);
	}

	if (isValid == false) {
		cout << "IMPOSSIBLE" << nextl;
	}
	else
	{
		reverse(visited.begin(), visited.end());
		
		for (int i = 1; i < visited.size(); i++)
		{
			if (i > 1) cout << " ";
			cout << adjString[visited[i - 1]][visited[i]].back();
			adjString[visited[i - 1]][visited[i]].pop_back();
		}

		cout << nextl;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;
	while (numCase--) {
		for (int i = 0; i < 26; i++)
		{
			for (int j = 0; j < 26; j++)
			{
				adjString[i][j].clear();
			}
		}
		adj = vector<vector<int>>(26, vector<int>(26, 0));
		memset(inflow, 0, sizeof(inflow));
		memset(outflow, 0, sizeof(outflow));
		dic.clear();
		
		cin >> numWord;
		for (int i = 0; i < numWord; i++)
		{
			string temp;
			cin >> temp;
			dic.emplace_back(temp);
			adjString[temp.front() - 'a'][temp.back() - 'a'].push_back(temp);
			adj[temp.front() - 'a'][temp.back() - 'a']++;
			outflow[temp.back() - 'a']++;
			inflow[temp.front() - 'a']++;
		}

		solve();
	}
}