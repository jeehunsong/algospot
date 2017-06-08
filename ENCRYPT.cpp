#include <iostream>
#include <string>

using namespace std;

int main()
{
	int cases;
	cin >> cases;
	while (cases--)
	{
		string input;
		cin >> input;

		for (int i = 0; i < input.size(); i += 2)
		{
			cout << input.at(i);
		}

		for (int i = 1; i < input.size() ; i += 2)
		{
			cout << input.at(i);
		}

		cout << endl;
	}
	return 0;
}