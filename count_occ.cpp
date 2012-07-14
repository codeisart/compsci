#include <vector>
#include <iostream>
#include <sstream>

template<typename ITERATOR, typename T>
ITERATOR find_linear(ITERATOR i, ITERATOR end, const T& v)
{
	for( ; i != end; ++i)
		if(v == *i)
			return i;

	return end;
}

template<typename ITERATOR, typename T>
int count_linear(ITERATOR i, ITERATOR end, const T& v)
{
	int count = 0;
	for( i = find_linear(i,end,v); i!= end; i = find_linear(i+1,end,v))
		count++;

	return count;		
}

template<typename ITERATOR, typename T>
ITERATOR find_binary(ITERATOR begin, ITERATOR end, const T& v)
{
	int left = 0;
	int right = std::distance(begin,end);
	
	if(right <=0)
		return end;
		
	while(left < right)
	{
		int mid = left + ((right-left) / 2);
		const T& midval = begin[mid];

		if(midval == v)
			return begin+mid;
		else if(midval < v)
			left = mid+1;
		else
			right = mid;
	}
	return end;
}

template<typename ITERATOR, typename T>
ITERATOR find_binary_recursive(ITERATOR begin, ITERATOR end, const T& v)
{
	int range = std::distance(begin,end);
	
	if(range <=0)
		return end;
		
	int mid = range / 2;
	const T& midval = begin[mid];

	if(midval == v)
		return begin+mid;
	else if (midval > v)
	{
		// Need to preseve the END
		ITERATOR right = begin+mid;	
		ITERATOR ret = find_binary_recursive(begin,right,v);
		if(ret == right)
			return end;
		else
			return right;	
	}
	else if(midval < v)
	{
		return find_binary_recursive(begin+mid+1,end,v);
	}
	
	return end;
}

template<typename ITERATOR, typename T>
int count_binary(ITERATOR i, ITERATOR end, const T& v)
{
	int count = 0;
	for( i = find_binary(i,end,v); i!= end; i = find_binary(i+1,end,v))
		count++;

	return count;		
}

template<typename ITERATOR, typename T>
int count_binary_recursive(ITERATOR i, ITERATOR end, const T& v)
{
	int count = 0;
	for( i = find_binary_recursive(i,end,v); i!= end; i = find_binary_recursive(i+1,end,v))
		count++;

	return count;		
}

int main(int argc, const char** argv)
{
	using namespace std;

	if(argc <= 1)
	{
		cerr << "# to count occurances of required." << endl;
		return -1;
	}

	int number;
	stringstream(argv[1]) >> number;

	int c;
	vector<int> numbers;
	while(cin >> c)
		numbers.push_back(c);

	sort(numbers.begin(),numbers.end());

	for(vector<int>::const_iterator i = numbers.begin(); i!= numbers.end(); ++i)
		cout << *i << ",";

	cout << endl;

	//int count = count_linear(numbers.begin(),numbers.end(),number);
	//int count = count_binary(numbers.begin(),numbers.end(),number);
	int count = count_binary_recursive(numbers.begin(),numbers.end(),number);
	cout << "Occurances of " << number << "=" << count << endl;

	return 0;
}
