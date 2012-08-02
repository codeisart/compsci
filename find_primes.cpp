#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <future>

typedef std::vector<int> Col;

template<typename ITER>
inline bool isPrime(int n, ITER begin, ITER end)
{
	//c++11
	auto divisor = std::find_if(
		begin,end,[&](int i) 
			{ return n % i == 0; } 
	);

	return divisor == end;

	//for(Col::const_iterator i = primes.begin(); i!= primes.end(); ++i)
	//	if(n % *i == 0)
	//		return false;		
	//return true;
}

int main(int argc, char** argv)
{
	using namespace std;
	vector<int> primes;

	int toFind = 100;

	if(argc>1)
		std::stringstream(argv[1]) >> toFind;

	std::cout << "looking for " << toFind << " primes" << std::endl;

	int i = 3;
	primes.push_back(2);
	while(primes.size() < toFind)
	{
		int n = std::min(primes.size(),(size_t)200);
		if(isPrime(i,primes.begin(),primes.begin()+n))
		{
			std::cout << i << std::endl;
			std::cerr << i << std::endl;
			primes.push_back(i);
		}
		i+=2;
		if(i % 100)
			std::cerr << ".";
	}

	return 0;
}


