#include <vector>
#include <iostream>

using namespace std;

inline int min(int a, int b) { return a > b ? b : a; }
inline int max(int a, int b) { return a > b ? a : b; }

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
		return min(	query(left, right, node * 2, nodeLeft, mid),
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
#if 0 
int main()
{
	vector<int> a{ 1, 2, 6, 4, 5, 3, 9, 8 };

	RMQ rmq(a);

	for (auto i : rmq.rangeMin)
		cout << i << ' ';
	cout << endl << endl;

	cout << "minval 0 ~ 7 " << rmq.query(0, 7) << endl;
	cout << "minval 1 ~ 3 " << rmq.query(1, 3) << endl;
	cout << "minval 5 ~ 7 " << rmq.query(5, 7) << endl;
	cout << endl;
	
	a[5] = 0;
	rmq.update(5, 0);
	for (auto i : rmq.rangeMin)
		cout << i << ' ';
	cout << endl << endl;

}
#endif