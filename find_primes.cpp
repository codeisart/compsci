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
	//std::cout << "start findPrimes - " << rangeStart << " " << rangeEnd << " primes_size=" << earlyPrimes.size() << std::endl;

	Col newlyFound;
	if((rangeStart & 1) == 0)
		rangeStart++;

	for(int i = rangeStart; i < rangeEnd; i+=2)
	{
		if(isPrime(i,earlyPrimes.begin(), earlyPrimes.end()))
			newlyFound.push_back(i);
	//	if(i % 100)
	//		std::cout << ".";
	}

	//std::cout << "end findPrimes" << rangeStart << " " << rangeEnd << " " << newlyFound.size() << std::endl;

	return newlyFound;
}

int main(int argc, char** argv)
{
	static const size_t earlyPrimesNum = 200;
	static const size_t primesSearchRange = 50000;

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
	int threads = toFind;			
	int range = earlyPrimes.back() + 1;
	for(int i = 0; i < threads; i++)
	{
		std::cerr << "spawning thread " << i << " for range " << range << "-" << range+primesSearchRange << std::endl;
		results.push_back(
			std::async(
				std::launch::async,
				[range,earlyPrimes] { return findPrimes(range,range+primesSearchRange,earlyPrimes); })
		);
		range += primesSearchRange;
	}
	for(auto &i: results)
	{
		const auto &j = i.get();
		mergedResults.insert(mergedResults.end(),j.cbegin(),j.cend());	
	}

	std::sort(mergedResults.begin(), mergedResults.end());
	for(const auto &i: mergedResults)
		cout << i << endl;
	
	return 0;
}


