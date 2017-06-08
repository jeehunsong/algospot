#include <iostream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

inline int max(int a, int b)
{
	return (a > b ? a : b);
}

int numThings, carrierCapacity;

struct package {
	string name;
	int volume;
	int desperation;
};

vector<package> inform;
int cache[1001][1001];

int packing(int order, int capacityLeft)
{
	if ((capacityLeft < 0) || (order >= numThings))
	{
		return 0;
	}

	int & ret = cache[order][capacityLeft];

	if (ret != -1)
	{
		return ret;
	}

	ret = 0;

	//numThings 번째 물건 (마지막 물건)
	if (order == (numThings - 1))
	{
		if (capacityLeft >= inform[order].volume)
		{
			ret = inform[order].desperation;
		}
		return ret;
	}

	ret = packing(order + 1, capacityLeft);
	if (capacityLeft >= inform[order].volume)
	{
		ret = max(ret, packing(order + 1, capacityLeft - inform[order].volume) + inform[order].desperation);
	}
	return ret;
}

vector<string> choice;

int packing2(int order, int capacityLeft)
{
	//order 는 이미 넣었다.
	if ((capacityLeft < 0) || (order > numThings))
	{
		return 0;
	}

	int & ret = cache[order][capacityLeft];

	if (ret != -1)
	{
		return ret;
	}

	ret = 0;

	//order 번째 이후 모든 케이스에 대해 넣을지를 결정한다.
	int bestNext = -1;
	for (int next = order + 1; next <= numThings; next++)
	{
		if (inform[next - 1].volume <= capacityLeft)
		{
			//order 다음에 next를 넣는 경우에 대해 고려한다.
			int temp = packing2(next, capacityLeft - inform[next - 1].volume) + inform[next - 1].desperation;

			if (ret < temp)
			{
				//bestNext = next;
				ret = temp;
			}
		}
	}

	//choice[order] = bestNext;

	return ret;
}

void reconstruct(int capacity, int item)
{
	if (item == numThings)
	{
		return;
	}
	if (packing2(item, capacity) == packing2(item + 1, capacity))
	{
		reconstruct(capacity, item + 1);
	}
	else
	{
		choice.push_back(inform[item].name);
		reconstruct(capacity - inform[item].volume, item + 1);
	}
}

int main()
{
	int cases;

	cin.sync_with_stdio(false);
	cin >> cases;

	while (cases--)
	{
		cin >> numThings >> carrierCapacity;

		inform.clear();
		memset(cache, -1, sizeof(cache));
		

		for (int i = 0; i < numThings; i++)
		{
			package temp;
			cin >> temp.name >> temp.volume >> temp.desperation;
			inform.push_back(temp);
		}

		int maxDesperation;
		maxDesperation = packing2(0, carrierCapacity);
		choice.clear();
		reconstruct(carrierCapacity, 0);

		cout << maxDesperation << ' ' << choice.size() << '\n';
		for (int i = 0; i < choice.size(); i++)
		{
			cout << choice[i] << '\n';
		}
	}
	return 0;
}