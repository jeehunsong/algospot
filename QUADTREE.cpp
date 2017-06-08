#include <iostream>
#include <string>

#define FOR(i,n) for(int i = 0 ; i < n; i++)

using namespace std;

string input, output;

string reverse(string::iterator & it)
{
	char head = *it;

	++it;

	if ((head == 'b') || (head == 'w'))
	{
		return string(1, head);
	}
	string upperLeft = reverse(it);
	string upperRight = reverse(it);
	string lowerLeft = reverse(it);
	string lowerRight = reverse(it);

	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

int main()
{
	int cases;
	cin >> cases;
	while (cases--)
	{
		input.clear();
		output.clear();
		cin >> input;

		auto it = input.begin();

		output = reverse(it);

		cout << output << endl;
	}
	return 0;
}