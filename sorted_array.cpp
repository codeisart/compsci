#include <iostream>
#include <vector>
//#include <algorthmn>

typedef std::vector<int> VecInt;


void mergeSortedInToLarger(VecInt& large, const VecInt& small, int largeUsed)
{
	int largeIndex = 0;
	int smallIndex = 0;

	while(largeIndex < largeUsed && 
		  smallIndex < small.size())
	{
		int s = small[smallIndex];
		int l = large[largeIndex];
		if(s < l)
		{
			for(int i = largeUsed; i!= largeIndex; i--)
				large[i] = large[i-1];		

			large[largeIndex++] = small[smallIndex++];
		}
		else
			largeIndex++;			
	}

	std::cout << "index = " << largeIndex << std::endl;
	while(smallIndex < small.size())
		large[largeIndex++] = small[smallIndex++];
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

	//int c;
	//while(cin >> c)
	//	numbers.push_back(c);
	//sort(numbers.begin(), numbers.end());

	vector<int> numbers2 = numbers;	
	vector<int> results;

	int odd[] = { 1,3,5,7,9,11,13,15,17,19 };
	int mostley_even[] = {2,4,6,8};

	numbers.insert(numbers2.begin(),odd,odd+sizeof_array(odd));
	numbers2.insert(numbers2.begin(),mostley_even,mostley_even+sizeof_array(mostley_even));
	numbers2.resize(numbers.size()*2);
		
	for(VecInt::const_iterator i = numbers2.begin(); i!= numbers2.end(); ++i)
		cout << *i << " ";

	cout << endl;
	mergeSortedInToLarger(numbers2,numbers,numbers.size());

	for(VecInt::const_iterator i = numbers.begin(); i!= numbers.end(); ++i)
		cout << *i << " ";

	cout << endl;
	for(VecInt::const_iterator i = numbers2.begin(); i!= numbers2.end(); ++i)
		cout << *i << " ";

	cout << endl;

	//results.resize(numbers.size()+numbers2.size());
	//mergeSorted(numbers, numbers2, results);
	//for(VecInt::const_iterator i = results.begin(); i!= results.end(); ++i)
	//	cout << *i << " ";
	//cout << endl;
}
