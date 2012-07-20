#include <iostream>
#include <sstream>
#include <unordered_map> // Cx11
#include <vector>
//#include "hash_table.cpp"	// oh for a make file.

using namespace std;

pair<int,int>
find_pair(int v, int arr[], int n)
{
//	typedef HashTable<int,int> FreqMap;
	typedef unordered_map<int,int> FreqMap;

	FreqMap map;
	for(int i = 0; i < n; ++i)
		map[arr[i]]++;
	
	for(int i = 0; i < n; ++i)
	{
		int d = v-arr[i];
		if(map[d]>0)
			return pair<int,int>(arr[i],d);
	}	
	return pair<int,int>();
}

int main(int argc, char** argv)
{
	if(argc<=1)
	{
		cout << "please type the value for V" << endl;
		return 0;
	}
	int v=0;
	stringstream(argv[1]) >> v;

	vector<int> numbers;
	int n=0;
	while(cin >>n)
		numbers.push_back(n);

	pair<int,int> result = find_pair(v,&numbers[0], numbers.size());

	// Assume the results are non-zero.
	if(result.first && result.second)
		cout << "Pair: " << result.first << "," << result.second << endl;

	return 0;
}
