#include <iostream>
#include <string>
#include <sstream>

using namespace std;

typedef unsigned int u32;

template<int N>
int count_bits(u32 i)
{	
	return (((1 << N) & i) != 0) + count_bits<N-1>(i); 
}
template<>
int count_bits<0>(u32 i)
{	
	return i & 1;
}

int main(int argc, char** argv)
{
	if(argc <=1)
	{
		cout << "please supply a number to count the bit of" << endl;
		return 0;
	}

	u32 n;
	stringstream(argv[1]) >> n;
	cout << count_bits<31>(n);
	
	return 0;
}
