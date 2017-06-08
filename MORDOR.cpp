#include <vector>
#include <iostream>

using namespace std;

inline int min(int a, int b) { return a > b ? b : a; }
inline int max(int a, int b) { return a > b ? a : b; }
#define nextl '\n'


struct RMQ {
	int n;
	vector<int> rangeMin;

	RMQ(const vector<int> & array) {
		n = array.size();
		rangeMin.resize(4 * n);
		init(array, 0, n - 1, 1);
	}

	int init(const vector<int> & array, int left, int right, int node) {
		// ���� ���̰� 1�� ��� �� ���� ��ü�� �ּҰ�
		if (left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}

	// node �� ���� �׽�Ʈ �ϴ� ���. node�� [nodeLeft nodeRight] ������ �׽�Ʈ��.
	// left right�� ��ͽ� �Һ�.
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		// ��ġ�� �ʴ� ��� => �׽�Ʈ �� ������ ����.
		if (right < nodeLeft || nodeRight < left) return 0x7FFFFFFF;

		// nodeLeft, nodeRight �� left right�� ���ԵǸ� �� ���ȣ�� �� �ʿ� ���� �����ϸ� ��.
		if (left <= nodeLeft && nodeRight <= right)	return rangeMin[node];

		int mid = (nodeLeft + nodeRight) / 2;
		return min(query(left, right, node * 2, nodeLeft, mid),
			query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	// �ܺο��� ȣ���ϴ� �Լ�
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}

	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		// ��ġ�� �ʴ� ��� �����Ѵ�.
		if (index < nodeLeft || nodeRight < index) return rangeMin[node];
		if (nodeLeft == nodeRight) return rangeMin[node] = newValue;
		int mid = (nodeLeft + nodeRight) / 2;
		return rangeMin[node] = min(update(index, newValue, node * 2, nodeLeft, mid),
			update(index, newValue, node * 2 + 1, mid + 1, nodeRight));
	}

	int update(int index, int newValue) {
		return update(index, newValue, 1, 0, n - 1);
	}
};


int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;
	while (numCase--) {
		int numSign, numRoad;
		vector<int> sign, signNegative;
		cin >> numSign >> numRoad;
		
		for (int i = 0; i < numSign; i++)
		{
			int temp;
			cin >> temp;
			sign.push_back(temp);
			signNegative.push_back(temp * -1);
		}

		RMQ rmq(sign), rmqNegative(signNegative);
		
		for (int i = 0; i < numRoad; i++)
		{
			int left, right;
			cin >> left >> right;
			cout << (rmq.query(left, right) + rmqNegative.query(left, right)) * -1 << endl;
		}
	}
}