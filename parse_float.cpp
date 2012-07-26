#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int ctoi(char c)
{
	return c-'0';
}

int parseInt(string s)
{
	// Parse each piece into an int.
	int integer = 0;
	for(auto i : s)
	{
		integer *=10;
		integer += ctoi(i);		
	}
	return integer;
}

float parseFloat(string s)
{
	// Assuming s is a valid string float with no-widespace
	float value = 0.0f;

	// Find the "."
	auto dot = std::find(s.begin(),s.end(),'.');

	// Split into mantissa and exponent.
	string mantissa(dot+1,s.end());
	string exponent(s.begin(),dot);

	float m = static_cast<float>(parseInt(mantissa));
	value = static_cast<float>(parseInt(exponent));

	while((int)m > 0)
		m /= 10.0;

	value += m;
	return value;
}

int main(int argc, char** argv)
{
	if(argc <=1)
	{
		std::cout << "please supply a number to parse" << std::endl;
		return -1;
	}

	string number(argv[1]);
	float value = parseFloat(number);

	cout << value << endl;

	return 0;
}
