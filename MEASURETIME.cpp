#include <iostream>
#include <vector>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

struct FenwickTree {
	vector<int> tree;
	FenwickTree(int n) : tree(n + 1) {}

	int sum(int pos) {
		++pos;
		int ret = 0;
		while (pos > 0) {
			ret += tree[pos];
			pos &= (pos - 1);
		}
		return ret;
	}

	void add(int pos, int val) {
		++pos;
		while (pos < tree.size()) {
			tree[pos] += val;
			pos += (pos & -pos);
		}
	}
};

int n;

long long countMoves(const vector<int>& A) {
	FenwickTree tree(1000000);
	long long ret = 0;
	for (int i = 0; i < A.size(); i++)
	{
		ret += tree.sum(999999) - tree.sum(A[i]);	// A[i] 이상인 수의 개수
		tree.add(A[i], 1);
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
		vector<int> A;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			int a;
			cin >> a;
			A.push_back(a);
		}
		cout << countMoves(A) << nextl;
	}

	return 0;
}