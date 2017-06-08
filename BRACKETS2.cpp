#include <iostream>
#include <string>
#include <stack>

using namespace std;
#define MIN(x, y)	((x) > (y) ? (y) : (x))
#define MAX(x, y)	((x) > (y) ? (x) : (y))
#define nextl '\n'

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;
	cin.ignore();

	while (numCase--)
	{
#if 1
		string input;
		getline(cin, input);
#endif
		stack<char> bracketStack;

		bool success = true;
		for (auto curChar = input.begin() ; curChar != input.end(); curChar++)
		{
			if (*curChar == '(' || *curChar == '{' || *curChar == '[')
			{
				bracketStack.push(*curChar);
			}
			else if ((!bracketStack.empty()) &&
				((bracketStack.top() == '(' && *curChar == ')') || (bracketStack.top() == '{' && *curChar == '}') || (bracketStack.top() == '[' && *curChar == ']') ))
			{
				bracketStack.pop();
			}
			else {
				success = false;
				break;
			}
		}
		if (success == true && bracketStack.empty()) {
			cout << "YES" << nextl;
		}
		else
			cout << "NO" << nextl;
	}

	return 0;
}