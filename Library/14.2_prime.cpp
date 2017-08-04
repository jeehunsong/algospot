#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

bool isPrime(int n)
{
	if (n == 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	int sqrtn = int(sqrt(n));
	for (int div = 3; div <= sqrtn; div += 2)
	{
		if (n % div == 0)
			return false;
	}
	return true;
}

vector<int> factorSimple(int n)
{
	vector<int> ret;
	int sqrtn = int(sqrt(n));
	for (int div = 2; div <= sqrtn; div++)
	{
		while (n % div == 0) {
			n /= div;
			ret.push_back(div);
		}
	}
	// In the case of prime number n
	if (n > 1) ret.push_back(n);
	return ret;
}

vector<bool> eratosthenes(int n) {
	vector<bool> isPrime(n + 1, true);
	isPrime[0] = isPrime[1] = false;
	int sqrtn = int(sqrt(n));
	for (int i = 2; i <= sqrtn; i++)
	{
		if (isPrime[i] == true) {
			for (int j = i*i; j <= n ; j += i)
			{
				isPrime[j] = false;
			}
		}
	}
	return isPrime;
}

int gcd(int p, int q) {
	if (p < q) swap(p, q);
	if (q == 0) return p;
	return (q, p % q);
}

int main()
{
#if 0
	vector<int> factor = factorSimple(100);
	for (auto i : factor)
		cout << i << " ";
	cout << endl;
#endif

#if 0
	cout << isPrime(121) << endl;
	cout << isPrime(199) << endl;
	cout << endl;
#endif

#if 0
	vector<bool> eratos = eratosthenes(300);
	for (int i = 0; i < eratos.size(); i++)
		cout << i << ": " << eratos[i] << endl;
#endif


}