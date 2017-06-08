#include <iostream>
#include <string>
#include <sstream>

using namespace std;
int main()
{
	int cases;
	cin >> cases;
	while (cases--)
	{
		int max;
		string input;
		stringstream inputStream;
		int eachRoomPowerConsumption;

		cin >> max;
		cin.ignore();
		//cin.clear 는 안된다.
		getline(cin, input);
		inputStream.str(input);

		while (inputStream >> eachRoomPowerConsumption)
		{
			max -= eachRoomPowerConsumption;
		}

		if (max < 0)
		{
			cout << "NO" << endl;
		}
		else
		{
			cout << "YES" << endl;
		}
	}
	return 0;
}