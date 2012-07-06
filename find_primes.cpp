#include <vector>
#include <iostream>
#include <sstream>

typedef std::vector<int> Col;

bool isPrime(int n, const Col& primes)
{
	for(Col::const_iterator i = primes.begin(); i!= primes.end(); ++i)
		if(n % *i == 0)
			return false;		

	return true;
}

int main(int argc, char** argv)
{
	using namespace std;
	vector<int> primes;

	int toFind = 100;

	if(argc>1)
		std::stringstream(argv[1]) >> toFind;

	std::cout << "looking for " << toFind << " primes" << std::endl;

	int i = 2;
	while(primes.size() < toFind)
	{
		if(isPrime(i,primes))
		{
			std::cout << i << std::endl;
			std::cerr << i << std::endl;
			primes.push_back(i);
		}
		i++;
		if(i % 100)
			std::cerr << ".";
	}
	

	return 0;
}


