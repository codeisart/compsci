#include <iostream>
#include <sstream>
#include <vector>

typedef unsigned long long int fib_num;

fib_num fib_recursive(int n)
{
	if(n <= 0)
		return 0;
	else if(n == 1)
		return 1;

	return fib_recursive(n-1) + fib_recursive(n-2);
}

fib_num fib_norec(int n)
{
	const int kStartVals[] = {0,1};
	std::vector<int> vals(kStartVals,kStartVals+2);
	vals.resize(n+1);

	for(int i = 2; i <= n; ++i)
		vals[i] = vals[i-1]+vals[i-2];
	
	for(std::vector<int>::const_iterator i = vals.begin(); i!=vals.end(); ++i)
		std::cerr << *i << std::endl;
	
	return vals[n];
}

int main(int argc, char** argv)
{
	using namespace std;

	int n = 0;
	if(argc <= 1)
	{
		cout << "Pass through N value as first argument." << endl;
		return -1;
	}

	stringstream(argv[1]) >> n;	
	cout << "Generating FIB " << n << " = ";
	//fib_num result = fib_recursive(n);
	fib_num result = fib_norec(n);
	cout << result << endl;

	return 0;
}
