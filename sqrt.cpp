#include <iostream>
#include <vector>

// Very slow way of finding a square root.
float my_sqrt(float v)
{
	if(v < 0)
		return -1.f;
	
	if(v == 0 || v == 1)
		return v;

	const float max_precision = 0.00001f;
	float left = 0.0f;
	float right = v;
	float mid = 0.0f;
	while(right-left > max_precision)
	{
		mid = left + ((right-left) / 2.f);
		float sqr = mid*mid;

		//std::cerr << "mid = " << mid << std::endl;
		//std::cerr << "left = " << left << std::endl;
		//std::cerr << "right = " << right << std::endl;
		
		// Found it exactly! woot.
		if(sqr == v)
			return mid;
		else if(sqr < v)
			left = mid;
		else 
			right = mid;
	}
	return mid;
}

int main(int argc, char** argv)
{
	using namespace std;

	vector<int> numbers;
	int c;
	while(cin >> c)
		numbers.push_back(c);

	for(vector<int>::const_iterator i=numbers.begin(); i!= numbers.end(); ++i)
		cout << "sqrt of " << *i << " = " << my_sqrt((float)*i) << endl;
}




