#include <iostream>
#include <vector>

template<typename T>
inline void swp(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}


template<>
inline void swp(int& a, int& b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}


template<typename IT>
inline void bubble(IT b, IT e)
{
	bool sorted;	
	do
	{
		sorted = true;
		for(IT i = b; i != e-1; ++i)
		{
			if(*i > *(i+1))
			{
				swp(*i,*(i+1));
				sorted = false;
			}
		}
	} while(!sorted);
}

template<typename IT>
inline void bubble2(IT b, IT e)
{
	bool sorted;
	int top = 1;	
	do
	{
		sorted = true;
		for(IT i = b; i != e-top; ++i)
		{
			if(*i > *(i+1))
			{
				swp(*i,*(i+1));
				sorted = false;
			}
		}
		top++;
	} while(!sorted);
}

int powerOf2GreaterThanN(int n)
{
	int p = 0;
	while((1 << p) < n)
		p++;

	return p;	
}

template<typename IT>
void merge_exchange(IT b, IT e)
{
	std::cout << "merge_exchange" << std::endl;
	int n = std::distance(b,e);
	int t = powerOf2GreaterThanN(n);		// logN

	//std::cout << " N is " << n;
	//std::cout << " t is " << t;
	//std::cout << std::endl;

	for(int p = 1 << (t-1); p > 0; p >>=1)
	{
		//std::cout << "         . p = " << p << std::endl;
		
		int q = 1<<(t-1);
		int r = 0;
		int d = p; 
            		
		do
		{
			//std::cout << " p is " << p << std::endl;
			//std::cout << " q is " << q << std::endl;
			//std::cout << " r is " << r << std::endl;
			//std::cout << " d is " << d << std::endl;
			//std::cout << " -=-=-=-=-=-=" << std::endl;

			int i = 0;
			do
			{
				//std::cout << "n-d=" << n-d << ", i&p=" << ((i-1)&p) << ", r = " << r << std::endl;	
				//std::cout << ",";
				if( b[i] > b[i+d])
				{
					swp(b[i], b[i+d]);
					//std::cout << "swp" << std::endl;
				}
				
				if(i>=n-d || i&p != r)
					break;
				
				i++;
			}while(1);
			
			if(q==p)
				break;
			d = q-p;
			q >>= 1;
			r = p;
		} while(1);
		 
	}
}

int main(int argc, char** argv)
{	
	using namespace std;
	vector<int> numbers;
	int c;
	while(std::cin >> c)
	{
		numbers.push_back(c);
		std::cout << c << std::endl;
	}

	cout << " read " << numbers.size() << endl;
	cout << " sorting...";

	//bubble2(numbers.begin(),numbers.end());
	merge_exchange(numbers.begin(),numbers.end());

	cout << " done" << endl;

	for(vector<int>::const_iterator i = numbers.begin(); i!= numbers.end(); ++i)
		cout << *i << endl;

	return 0;
}
