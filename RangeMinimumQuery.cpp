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
		// 구간 길이가 1인 경우 그 구간 자체가 최소값
		if (left == right)
			return rangeMin[node] = array[left];
		int mid = (left + right) / 2;
		int leftMin = init(array, left, mid, node * 2);
		int rightMin = init(array, mid + 1, right, node * 2 + 1);
		return rangeMin[node] = min(leftMin, rightMin);
	}

	// node 가 현재 테스트 하는 노드. node는 [nodeLeft nodeRight] 구간을 테스트함.
	// left right는 재귀시 불변.
	int query(int left, int right, int node, int nodeLeft, int nodeRight) {
		// 겹치지 않는 경우 => 테스트 할 이유가 없음.
		if (right < nodeLeft || nodeRight < left) return 0x7FFFFFFF;

		// nodeLeft, nodeRight 가 left right에 포함되면 더 재귀호출 할 필요 없이 리턴하면 됨.
		if (left <= nodeLeft && nodeRight <= right)	return rangeMin[node];

		int mid = (nodeLeft + nodeRight) / 2;
		return min(	query(left, right, node * 2, nodeLeft, mid),
					query(left, right, node * 2 + 1, mid + 1, nodeRight));
	}

	// 외부에서 호출하는 함수
	int query(int left, int right) {
		return query(left, right, 1, 0, n - 1);
	}

	int update(int index, int newValue, int node, int nodeLeft, int nodeRight) {
		// 겹치지 않는 경우 무시한다.
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