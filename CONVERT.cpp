#include <iostream>
#include <string>
#include <math.h>

using namespace std;

#define KG_TO_LB	2.2046
#define LB_TO_KG	0.4536
#define L_TO_G		0.2642
#define G_TO_L		3.7854

int main()
{
	int cases;
	cin >> cases;
	for (int idxCases = 1; idxCases <= cases; idxCases++)
	{
		string unit, unitConverted;
		double input, output;

		cin >> input >> unit;

		if (unit.compare("kg") == 0 )
		{
			output = (double)input * KG_TO_LB;
			unitConverted = "lb";
		}
		else if (unit.compare("lb") == 0)
		{
			output = (double)input * LB_TO_KG;
			unitConverted = "kg";
		}
		else if (unit.compare("l") == 0)
		{
			output = (double)input * L_TO_G;
			unitConverted = "g";
		}
		else if (unit.compare("g") == 0)
		{
			output = (double)input * G_TO_L;
			unitConverted = "l";
		}
		double p = pow(10, 4);
		output = floor((output * p) + 0.5f) / p;
		printf("%d %.4lf %s\n", idxCases, output, unitConverted.c_str());
	}

	return 0;
}