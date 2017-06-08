#include <iostream>
#include <string>

union endian {
	unsigned int a;
	char byte[4];
};

using namespace std;
int main()
{
	int cases;
	cin >> cases;
	while (cases--)
	{
		endian input, output;
		cin >> input.a;

		for (int i = 0; i < 4; i++)
		{
			output.byte[3 - i] = input.byte[i];
		}
		

		cout << output.a <<endl;
	}
	return 0;
}