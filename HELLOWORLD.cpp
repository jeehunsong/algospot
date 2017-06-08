#include <iostream>
#include <string>

#define FOR(i,n)	for(int i = 0 ; i < n ; i++)

using namespace std;

int main()
{
	int cases;
	
	cin.sync_with_stdio(false);
	cin >> cases;

	while (cases--)
	{
		string name;
		cin >> name;

		cout << "Hello, " << name << "!" << '\n';
	}
	return 0;
}