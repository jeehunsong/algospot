#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int cases;
	cin >> cases;
	while (cases--)
	{
		string input;
		vector<string> output;
		cin >> input;

		int i = 0;
		while (i < input.size())
		{
			output.push_back(input.substr(i, 2));
			i += 2;
		}

		sort(output.begin(), output.end());

		for (auto i = output.begin() ; i != output.end() ; i++)
		{
			cout << *i;
		}
		cout << endl;
	}
	return 0;
}