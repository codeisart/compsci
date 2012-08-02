#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <future>

typedef std::vector<int> Col;
typedef std::future<Col> FutureCol;
typedef std::vector<FutureCol> Results;

template<typename ITER>
inline bool isPrime(int n, ITER begin, ITER end)
{
	//c++11
	auto divisor = std::find_if(
		begin,end,[&](int i) 
			{ return n % i == 0; } 
	);

	return divisor == end;
}

Col findPrimes(int rangeStart, int rangeEnd, const Col& earlyPrimes)
{
	Col newlyFound;
	if(!rangeStart & 1)
		rangeStart++;

	for(int i = rangeStart; i < rangeEnd; i+=2)
		if(isPrime(i,earlyPrimes.begin(), earlyPrimes.end()))
			newlyFound.push_back(i);

	return newlyFound;
}

int main(int argc, char** argv)
{
	static const size_t earlyPrimesNum = 200;
	static const size_t primesSearchRange = 1000;

	using namespace std;
	Col earlyPrimes;
	earlyPrimes.reserve(earlyPrimesNum);

	int toFind = earlyPrimesNum;

	if(argc>1)
		std::stringstream(argv[1]) >> toFind;

	std::cout << "looking for " << toFind << " primes" << std::endl;

	// Stage1 build early prime lookup.
	int i = 3;
	earlyPrimes.push_back(2);
	while(earlyPrimes.size() < earlyPrimesNum)
	{
		int n = std::min(earlyPrimes.size(),earlyPrimesNum);
		if(isPrime(i,earlyPrimes.begin(),earlyPrimes.begin()+n))
		{
			std::cout << i << std::endl;
			std::cerr << i << std::endl;
			earlyPrimes.push_back(i);
		}
		i+=2;
		if(i % 100)
			std::cerr << ".";
	}

	Col mergedResults(earlyPrimes);
	mergedResults.reserve(toFind);
	Results results;

	//  Stage2 dispatch multiple threads.
	for(int i = earlyPrimesNum; i; i+= primesSearchRange)
	{
		results.push_back(
			std::async([i,earlyPrimes] { return findPrimes(i,i+primesSearchRange,earlyPrimes); })
		);
	}
	
	return 0;
}


