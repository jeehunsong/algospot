#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> recipe, put;

int gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a % b);
}

int ceil(int a, int b) {
	return (a + b - 1) / b;
}

void solve() {
	vector<int> retVal(recipe.size());

	int gcdRecipe = recipe[0];
	for (auto i: recipe)
		gcdRecipe = gcd(gcdRecipe, i);

	int a = gcdRecipe;
	for (int i = 0; i < recipe.size(); ++i)
	{
		a = max(a, ceil(put[i] * gcdRecipe, recipe[i]));
	}
	for (int i = 0; i < recipe.size(); ++i)
	{
		retVal[i] = recipe[i] * a / gcdRecipe - put[i];
		cout << retVal[i] << " ";
	}
	cout << endl;
}

int main()
{
	int numCase;
	cin >> numCase;
	do
	{
		int n;
		cin >> n;
		recipe.clear();
		put.clear();
		recipe.resize(n);
		put.resize(n);

		for (int i = 0; i < n; ++i)
			cin >> recipe[i];
		for (int i = 0; i < n; ++i)
			cin >> put[i];

		solve();

	} while (--numCase);
}