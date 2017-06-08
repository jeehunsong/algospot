#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

int numNode;
vector<int> preorder, inorder;

vector<int> slice(const vector<int>& v, int a, int b) {
	return vector<int>(v.begin() + a, v.begin() + b);
}

void printPostOrder(const vector<int> & preorder, const vector<int>& inorder) {
	const int N = preorder.size();
	if (preorder.empty()) return;
	const int root = preorder[0];
	const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
	const int R = N - 1 - L;

	printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
	printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
	cout << root << ' ';
}

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;


	while (numCase--)
	{
		cin >> numNode;
		preorder.resize(numNode, 0);
		inorder.resize(numNode, 0);
		for (int i = 0; i < numNode; i++)
		{
			cin >> preorder[i];
		}
		for (int i = 0; i < numNode; i++)
		{
			cin >> inorder[i];
		}

		printPostOrder(preorder, inorder);
		cout << nextl;
	}

	return 0;
}