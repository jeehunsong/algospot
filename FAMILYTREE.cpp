#include <iostream>
#include <vector>

using namespace std;

#define nextl '\n'
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

const int MAX_N = 100000;
int n;
vector<int> child[MAX_N];
int no2serial[MAX_N], serial2no[MAX_N];
int locInTrip[MAX_N], depth[MAX_N];
int nextSerial;

void traverse(int here, int d, vector<int> & trip) {
	// serial�� 0������ ��ȸ�� ������� �����Ѵ�.
	no2serial[here] = nextSerial;
	serial2no[nextSerial] = here;
	++nextSerial;
	depth[here] = d;
	locInTrip[here] = trip.size();
	trip.push_back(no2serial[here]);
	for (int i = 0; i < child[here].size(); ++i) {
		traverse(child[here][i], d+1, trip);
		trip.push_back(no2serial[here]);
		// �̰� ��� �� �˰����� ��������...
		// �̰� ������ �ٸ� ����Ʈ���� �Ѿ �� ��� ������ ���� �� �� �� ����
	}
}

RMQ* prepareRMQ() {
	nextSerial = 0;
	vector<int> trip;
	traverse(0, 0, trip);
	return new RMQ(trip);
}

int distance(RMQ* rmq, int u, int v) {  
	int lu = locInTrip[u], lv = locInTrip[v];
	if (lu > lv) swap(lu, lv);
	int lca = serial2no[rmq->query(lu, lv)];
	return depth[u] + depth[v] - 2 * depth[lca];
}

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;
	while (numCase--) {
		int numPair;
		cin >> n >> numPair;
		
		for (int i = 0; i < n; i++)
		{
			child[i].clear();
		}

		for (int i = 1; i < n; i++)
		{
			int temp;
			cin >> temp;
			child[temp].push_back(i);
		}

		RMQ* rmq = prepareRMQ();


		for (int i = 0; i < numPair; i++) {
			int left, right;
			cin >> left >> right;
			cout << distance(rmq, left, right) << nextl;
		}
	}
}