#include <iostream>
#include <sstream>
#include "hash_table.cpp"	// oh for a make file.

using namespace std;

pair<int,int>
find_pair(int v, int arr[], int n)
{
	typedef HashTable<int,int> FreqMap;
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

int ctoi(char c)
{
	return c-'0';
}

int main(int argc, char** argv)
{
	if(argc<=2)
	{
		cout << "<numbers-in-a-string> <V>" << endl;
		return 0;
	}
	string str(argv[1]);
	int v = 0;
	stringstream(argv[2]) >> v;

	vector<int> numbers;
	for(string::const_iterator i = str.begin(); i!= str.end(); ++i)
		numbers.push_back(ctoi(*i));

	pair<int,int> result = find_pair(v,&numbers[0], numbers.size());
	cout << "Pair: " << result.first << "," << result.second << endl;

	return 0;
}
