#include <iostream>
#include <sstream>
#include <limits>

int gcd(int m,int n)
{
	// Eculids algorithm
	int r;
	while(r  = m % n)
	{
		 m = n;
		 n = r;
	}
	return n;
}

void printRational(float r)
{
	int power = 1;
	for(;;)
	{
		float r_power = (float)r*power;
		float fractional = (float)r_power - ((int)r_power);
		if(fractional == 0.0f)
			break;

		power*=10;
		std::cout << power << std::endl;
	}

	int upper = power*r;
	int lower = power;

	int gcdivisor = gcd(upper, lower);

	std::cout << "divisor " << gcdivisor << std::endl;

	upper /= gcdivisor;
	lower /= gcdivisor;
	
	//if(upper > lower)
	//	std::swap(lower,upper);

	std::cout << upper << "/" << lower << std::endl;
}

int main(int argc, char** argv)
{
	using namespace std;

	if(argc <=1)
	{
		cout << "please enter a rational number to parse" << endl;
		return -1;
	}

	float number;
	stringstream(argv[1]) >> number;
	
	printRational(number);	

}
