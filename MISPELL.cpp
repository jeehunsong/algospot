#include <iostream>
#include <string>

using namespace std;

int main()
{
	int cases;
	cin >> cases;
	for (int idxCase = 1; idxCase <= cases; idxCase++)
	{
		int inputInt;
		string inputString;
		cin >> inputInt >> inputString;
		
		cout << idxCase << " ";

		cout << inputString.substr(0, inputInt - 1);
		if (inputInt < inputString.size())
		{
			cout << inputString.substr(inputInt);
		}
		cout << endl;
	}
	return 0;
}