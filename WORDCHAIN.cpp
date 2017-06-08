// �ʾ��� ���� �ۼ�����
// ������� å ���� ����.


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

// vertex: ���ĺ�
// edge: �ܾ�
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
	// ���� ġ������ ����� ����. ���� § �ڵ�� edge�� �־��µ�, �׷��� ���� ���ڸ� �ְ� ���߿� edge�� ������ �ȴ�.
}

bool dfsAll(int start) 
{
	visited.clear();

	// �־��� �� ��ŸƮ
	if (start != -1)
		dfs(start);
	// ������ �� ��ŸƮ
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
	// alphabet�� ��ȸ�ϸ鼭 start-end�� ���� �� �ִ��� ����.
	bool isValid = true;
	int start = -1, end = -1;

	for (int i = 0; i < 26; i++)
	{
		//�������ΰ�?
		if (inflow[i] - outflow[i] == 1) {
			if (start == -1) start = i;
			else {
				isValid = false;
				break;
			}
		}
		//�����ΰ�?
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
		// ���� ���� OK
	}

	// ������/������ ���� invliad �� ��� ����
	if ((isValid == false) || (start == -1 && end != -1) ||	(start != -1 && end == -1)) 
	{
		isValid = false;
	}
	// ������, ������ Ư���� ���
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