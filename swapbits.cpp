#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

int bit_swap(int n, int pos)
{
	// a b  a1 b2
	// 0 0   0 0    
	// 0 1   1 0 
	// 1 0   0 1   
	// 1 1   1 1   

	int bit1 = n&1;
	int bit2 = (n>>1)&1;
	int newBits = (bit1 << 1)|bit2;
	if(!pos)
		return newBits;

	return (bit_swap(n>>2,pos-2) << pos) | newBits; 
}

int swap_bits(int n)
{
	static const int mask_odd = 1 | 1 << 3 | 1 << 5 | 1 << 7 | 1 << 9 | 1 << 11 | 1 << 13 | 1 << 15 | 1 << 17 | 1 << 19 | 1 << 21 | 1 << 23 | 1 << 25 | 1 << 27 | 1 << 29 | 1 << 31;
	static const int mask_even = 2 | 1 << 4 | 1 << 6 | 1 << 8 | 1 << 10 | 1 << 12 | 1 << 14 | 1 << 16 | 1 << 18 | 1 << 20 | 1 << 22 | 1 << 24 | 1 << 26 | 1 << 28 | 1 << 30;

	return ((n & mask_odd) << 1) | ((n & mask_even) >> 1);
	
/*
	for(int i = 0; i < 32; i+=2)
	{
		int tmp = n >> i;
		int bit1 = tmp&1;
		tmp>>=1;
		int bit2 = tmp&1;
		int newBits =  (bit2 | bit1 << 1) << i;
		int mask = 3 << i;
		n &= mask;
		n |= newBits;
	}
	return n;
*/
}


int main(int argc, char** argv)
{
	for(int i = 0; i < 256; ++i)
		cout << setw(10) << i << setw(10) << swap_bits(i) << setw(10) << bit_swap(i,32) << endl;
	return 0;
}
