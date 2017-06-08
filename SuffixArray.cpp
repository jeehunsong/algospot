#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct SuffixComparator {
	const string& s;
	SuffixComparator(const string& s) : s(s) {}
	bool operator () (int i, int j) {
		return strcmp(s.c_str() + i, s.c_str() + j) < 0;
	}
};

vector<int> getSuffixArrayNaive(const string& s) {
	vector<int> perm;
	for (int i = 0; i < s.size(); ++i)	perm.push_back(i);
	sort(perm.begin(), perm.end(), SuffixComparator(s));
	return perm;
}

struct Comparator {
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {	}
	bool operator () (int i, int j) {
		if (group[i] != group[j]) return group[i] < group[j];
		// 시작 위치에서 t 글자만큼 그룹이 같다면, 그 뒤에 대해서 t만큼 비교할 수 있다
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

int countSubstrings(const string& s) {
	vector<int> a = getSuffixArray(s);
	int ret = 0;
	int n = s.size();
	for (int i = 0; i < a.size(); ++i) {
		int cp = 0;
		if (i > 0) cp = commonPrefix(s, a[i - 1], a[i]);
		ret += s.size() - a[i] - cp;
	}
	return ret;
}