#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define PI 3.141592
//#define DEBUG

using namespace::std;

class myStack
{
public:
	myStack() {}
	~myStack() {}
	void push(char a);
	char pop();
	void clear();

private:
	vector<char> stack;
};

int main(int argc, char* argv[])
{
	string filename_input;
	string filename_output;

	if (argc == 1)
	{
		cout << "Input filename is not inserted" << endl;;
		filename_input = "Set1.in";
		filename_output = "Set1.out";
	}
	else
	{
		cout << "Input filename is " << argv[1];
		filename_input = argv[1];
		filename_input += ".in";
		filename_output = argv[1];
		filename_output += ".out";
	}

	ifstream fin(filename_input);
	ofstream fout(filename_output);
	string buff;

	while (getline(fin, buff))
	{
		//Input Handling
		cout << buff << endl;
		if (buff == "end")
		{
			break;
		}

		//Check each character
		myStack stack;
		char curBuff;
		char tempCharPopped;
		int curScore = 0, maxScore = 0;

		for (int idxBuff = 0 ; idxBuff < buff.size() ; idxBuff++)
		{
			curBuff = buff.at(idxBuff);
#ifdef DEBUG
			cout << curBuff << " : ";
#endif // DEBUG
			switch (curBuff)
			{
			case '(':
			case '[':
#ifdef DEBUG
				cout << "Pushed to Stack";
#endif // DEBUG
				stack.push(curBuff);
				break;
			case ')':
			case ']':
				tempCharPopped = stack.pop();
				if (tempCharPopped == '!')
				{
#ifdef DEBUG
					cout << "Stack underflow-";
#endif // DEBUG
					if (curScore > maxScore)
					{
#ifdef DEBUG
						cout << "Updated " << curScore;
#endif // DEBUG
						maxScore = curScore;
					}
				}
				else if (((tempCharPopped == '(') && (curBuff == ')')) || ((tempCharPopped == '[') && (curBuff == ']')))
				{
#ifdef DEBUG
					cout << "++ curScore-";
#endif // DEBUG
					curScore += 2;
				}
				else
				{
#ifdef DEBUG
					cout << "end of current stack-";
#endif // DEBUG
					stack.clear();
					if (curScore > maxScore)
					{
#ifdef DEBUG
						cout << "Updated " << curScore;
#endif // DEBUG
						maxScore = curScore;
					}
				}
				break;
			default:
				cout << "End of Test" << endl;
				break;
			}
#ifdef DEBUG
			cout << endl;
#endif // DEBUG
		}
		if (curScore > maxScore)
		{
#ifdef DEBUG
			cout << "Updated " << curScore << endl;
#endif // DEBUG
			maxScore = curScore;
		}

		cout << maxScore << endl;
	}

	fin.close();
	fout.close();
}

void myStack::push(char a)
{
	stack.push_back(a);
}

char myStack::pop()
{
	char retVal;
	if (stack.size() > 0)
	{
		retVal = *(stack.rbegin());
		stack.pop_back();
	}
	else
	{
		retVal = '!';
	}
	return retVal;
}

void myStack::clear()
{
	stack.clear();
}

