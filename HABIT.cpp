#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

struct Comparator {
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {	}
	bool operator () (int i, int j) {
		if (group[i] != group[j]) return group[i] < group[j];
		// ���� ��ġ���� t ���ڸ�ŭ �׷��� ���ٸ�, �� �ڿ� ���ؼ� t��ŭ ���� �� �ִ�
		return group[i + t] < group[j + t];
	}
};

vector<int> getSuffixArray(const string& s) {
	int n = s.size();

	int t = 1;
	vector<int> group(n + 1);
	for (int i = 0; i < n; ++i) group[i] = s[i];
	group[n] = -1;
	vector<int> perm(n);
	for (int i = 0; i < n; ++i) perm[i] = i;

	while (t < n) {
		Comparator compareUsing2T(group, t);
		sort(perm.begin(), perm.end(), compareUsing2T);

		t *= 2;
		if (t >= n) break;

		vector<int> newGroup(n + 1);
		newGroup[n] = -1;
		newGroup[perm[0]] = 0;
		for (int i = 1; i < n; ++i)
			if (compareUsing2T(perm[i - 1], perm[i]))
				newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
			else
				newGroup[perm[i]] = newGroup[perm[i - 1]];
		group = newGroup;
	}
	return perm;
}


int commonPrefix(const string & s, int i, int j) {
	int k = 0;
	while (i < s.size() && j < s.size() && s[i] == s[j]) {
		++i; ++j; ++k;
	}
	return k;
}

int longestFrequent(int k, const string& s) {
	vector<int> a = getSuffixArray(s);
	int ret = 0;
	for (int i = 0; i + k <= s.size(); ++i) {
		ret = max(ret, commonPrefix(s, a[i], a[i + k - 1]));
	}
	return ret;
}

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;
	

	while (numCase--)
	{
		int k;
		cin >> k;
		cin.ignore();
		string temp;
		getline(cin, temp);
		cout << longestFrequent(k, temp) << nextl;
	}

	return 0;
}