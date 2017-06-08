#include <iostream>
#include <string>
#include <vector>

#define FOR(i,n)	for(int i = 0 ; i < n ; i++)
//#define DEBUG

using namespace std;

const int divisor = 1000000007;

string priceEgg;
int numCandy;
vector<int> numPrice(10);

int exhaustCheck(const string past, int pos)
{
	int ret = 0;
#ifdef DEBUG
	cout << "Call Exht " << past << "\t\tpos " << pos << '\n';
#endif // DEBUG


	vector<int> left = numPrice;
	for (int i = 0; i < past.size(); i++)
	{
		left[(past.at(i) - '0')]--;
	}
	if (pos < priceEgg.size())
	{
		for (int i = 0; i < 10; i++)
		{
			if (left[i] > 0)
			{
				ret = (ret + exhaustCheck(past + to_string(i), pos + 1)) % divisor;
			}
		}
	}
	else
	{
		ret = (atoi(past.c_str()) % numCandy == 0);
	}
	
	return ret;
}

int compare(const string past, int pos)
{
	int ret = 0;
	int curPosNum = priceEgg.at(pos) - '0';
	
	vector<int> left = numPrice;
	for (int i = 0; i < past.size(); i++)
	{
		left[(past.at(i) - '0')]--;
	}

#ifdef DEBUG
	cout << "Call Comp " << past << "\t\tpos " << pos << '\n';
	FOR(i, 10)
	{
		cout << " " << left[i] << " ";
	}
	cout << '\n';
#endif // DEBUG


	//�ڸ������� ���� ���� �´�
	// ������ left�� ���ؼ��� ���� �� �������� �� ���Ѵ�.
	for (int i = 0; i < curPosNum; i++)
	{
		if (left[i] > 0)
		{
			vector<int> temp = left;
			temp[i]--;
			ret = (ret + exhaustCheck(past + to_string(i), pos + 1) % divisor);
		}
	}

	//�ڸ����� ���� ���� �´�.
	// ������ left�� ���ؼ� �ٽ� compare�� ������.
	if (left[curPosNum] > 0)
	{
		vector<int> temp = left;
		temp[curPosNum]--;
		//���ڸ��� ����
		if ((pos + 1) < priceEgg.size())
			ret = (ret + compare(past + to_string(curPosNum), pos + 1) % divisor);
		//else: ���� ������
	}

	return ret;
}

int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	while (cases--)
	{
		priceEgg.clear();
		numCandy = 0;
		cin >> priceEgg >> numCandy;

		fill(numPrice.begin(), numPrice.end(), 0);
		for (int i = 0; i < priceEgg.size(); i++)
		{
			numPrice[(priceEgg.at(i) - '0')]++;
		}
		
		
#ifdef DEBUG
		cout << "price of egg: " << priceEgg << endl;
		FOR(i, 10)
		{
			cout << " " << numPrice[i] << " ";
		}
		cout << '\n';
#endif // DEBUG


		cout << compare("", 0) << '\n';


	}
	return 0;
}