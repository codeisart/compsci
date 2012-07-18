#include <iostream>
#include <vector>
//#include <algorthmn>

typedef std::vector<int> VecInt;

template<typename ITERATOR>
void insertion_sort(ITERATOR start, ITERATOR end)
{
	int count = std::distance(start,end);
	for(int j = 1; j < count; ++j)
	{		
		int item = start[j];
		int hole = j;
		while(hole > 0 && start[hole-1] > item)
		{
			start[hole] = start[hole-1];
			hole--;
		}
		start[hole] = item;
	}
}


template<typename ITERATOR>
void print(ITERATOR start, ITERATOR end)
{
	for( ; start != end; start++)
		std::cout << *start << " ";
	std::cout << std::endl;
}

template<typename ITERATOR>
int mergeSortedInToLarger(ITERATOR dst, ITERATOR dstEnd, ITERATOR src, ITERATOR srcEnd, int dstUsed)
{
	ITERATOR dstUsedEnd = dst+dstUsed;
	while(dst != dstUsedEnd && src != srcEnd)
	{
		if(*src > *dst)
		{
			for(ITERATOR i = dstUsedEnd; i!= dst; i--)
				*dst = *(dst-1);

			*dst++ = *src++;
		}
		else
			src++;			
	}

	while(src != srcEnd)
		*dst++ = *src++;

	return dstUsed;
}

/*
void mergeSortedInToLarger(VecInt& a, const VecInt& b, int usedInA)
{
	int tailA = usedInA-1;
	int tailB = b.size()-1;
	
	while(tailA >= 0 && tailB >= 0)
	{
		if(a[tailA] > b[tailB])
		{
			a[tailA+tailB+1] = b[tailB];
			tailB--;
		}
		else
		{
			a[tailA+tailB+1] = a[tailA];
			tailA--;
		}
	}
	while(tailB >=0)
	{
		a[tailB] = b[tailB];
		tailB--;	
	}
}
*/

void mergeSorted(const VecInt& a, const VecInt& b, VecInt& out)
{
	VecInt::const_iterator i = a.begin(); 
	VecInt::const_iterator j = b.begin(); 
	
	while(i!= a.end() && j != b.end())
	{
		while(i!= a.end() && j!=b.end() && *i <= *j)
		{
			out.push_back(*i);
			i++;
		}
		
		while(i!= a.end() && j!= b.end() && *j <= *i)
		{
			out.push_back(*j);
			j++;
		}
	}
	for( ; i!=a.end(); ++i)
		out.push_back(*i);

	for( ; j!=b.end(); ++j)
		out.push_back(*j);
}

#define sizeof_array(array) int(sizeof(array)/sizeof(array[0]))

int main(int argc, char** argv)
{
	using namespace std;	
	vector<int> numbers;

	int c;
	while(cin >> c)
		numbers.push_back(c);
	
	print(numbers.begin(),numbers.end());
	insertion_sort(numbers.begin(), numbers.end());
	print(numbers.begin(),numbers.end());

	vector<int> numbers2 = numbers;	
	vector<int> results;

	int odd[] = { 1,3,5,7,9,11,13,15,17,19 };
	int mostley_even[] = {2,4,6,8};
	int knuth[] = {503, 87, 512,61,908,170,897,275,653,426,154,509,612,677,765,703};

	print(knuth,knuth+sizeof_array(knuth));
	insertion_sort(knuth,knuth+sizeof_array(knuth));
	print(knuth,knuth+sizeof_array(knuth));

	int longArray[] = {1,3,5,7,0,0,0,0};	
	int used = 4;//first 4 values are useful
	int shortArray[] = {2,4,6};

	print(shortArray,shortArray+sizeof_array(shortArray));	
	print(longArray,longArray+sizeof_array(longArray));	
	
	used = mergeSortedInToLarger(
		longArray,
		longArray+sizeof_array(longArray),
		shortArray,
		shortArray+sizeof_array(shortArray),
		used
	);

	print(longArray,longArray+sizeof_array(longArray));	
}
