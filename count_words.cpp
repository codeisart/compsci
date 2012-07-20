#include <unordered_map>
#include <future>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>

using WordStats = std::unordered_map<std::string,std::size_t>;

WordStats
wordsInFile(const char* const filename)
{
	std::ifstream file(filename);
	WordStats counts;
	
	for(std::string i; file >> i; )
		++counts[i];

	return counts;
}

template<typename ITERATOR>
void showCommonWords(ITERATOR begin, ITERATOR end, const std::size_t n)
{
	std::vector<ITERATOR> wordIterators;
	wordIterators.reserve(std::distance(begin,end));
	for(auto i = begin; i!= end; ++i) 
		wordIterators.push_back(i);

	auto sortedRangeEnd = wordIterators.begin() + n;
	std::partial_sort(wordIterators.begin(), sortedRangeEnd, wordIterators.end(),
					  [](ITERATOR l, ITERATOR r) 
					  { return l->second > r->second; });

	for(auto it = wordIterators.cbegin();
		it != sortedRangeEnd;
		++it)
	{
		std::printf(" %-10s%10zu\n", (*it)->first.c_str(), (*it)->second);
	}
}

int main(int argc, char** argv)
{
	std::vector<std::future<WordStats>> futures;

	for(int i = 1; i < argc; ++i)
	{
		futures.push_back(
			std::async([=]{ return wordsInFile(argv[i]); } )
		);
	}

	WordStats counts;
	for(auto& f : futures)
	{
		const auto& results = f.get();
		for( const auto& wordCount : results)
			counts[wordCount.first] += wordCount.second;
	}

	std::cout << counts.size() 
			  << " words found. Most Common:" << std::endl;
	const std::size_t maxWordsToShow = 20;
	showCommonWords(counts.begin(), counts.end(), std::min(counts.size(),maxWordsToShow));
}


