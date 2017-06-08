#include <iostream>
#include <string>
#include <queue>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'
template <int N> struct Power2 {
	static constexpr unsigned long long value = 2 * Power2<N - 1>::value;
};

template<> struct Power2<1> {
	static constexpr unsigned long long  value = 2;
};

int k, n;

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;


	while (numCase--)
	{
#if 0
		cin.ignore();
		string temp;
		getline(cin, temp);
#endif
		cin >> k >> n;
		
		int a = 1983;
		unsigned long long b = 1983, retVal = 0;
		//list<unsigned long long> sum;
		queue <int> myQueue;
		int rangeSum = 0;

		while (n--) {
			//�˰��� ������: �ᱹ ���� ���� ������ ��ȸ�ؾ� �ؼ�, KN�� ���������.
#if 0
			sum.push_back(0);
			auto i = sum.begin();
			while (i != sum.end())
			{
				*i += a;
				if (*i == k) {
					++retVal;
					++i;
					sum.pop_front();
				}
				else if (*i > k) {
					++i;
					sum.pop_front();
				}
				else {
					++i;
				}
			}
#endif
			// ť�� ���� �ְ�, ���� ��ü�� �ո� �����Ѵ�.
			myQueue.push(a);
			rangeSum += a;
			while (rangeSum > k) {
				rangeSum -= myQueue.front();
				myQueue.pop();
			}
			if (rangeSum == k)
				++retVal;

			a = b % 10000 + 1;
			b = (b * 214013 + 2531011) % Power2<32>::value;
		}
		cout << retVal << nextl;;
	}

	return 0;
}