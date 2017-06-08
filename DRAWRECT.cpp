#include <iostream>
#include <string>

using namespace std;

struct vertex {
	int x;
	int y;
};

int main()
{
	unsigned int cases;
	cin >> cases;
	while (cases--)
	{
		vertex input[3], output;
		output.x = 0;
		output.y = 0;

		for (int i = 0; i < 3; i++)
		{
			cin >> input[i].x >> input[i].y;
			output.x ^= input[i].x;
			output.y ^= input[i].y;
		}

		cout << output.x << " " << output.y << endl;
	}
	return 0;
}