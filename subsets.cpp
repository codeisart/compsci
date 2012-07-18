#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <map>

using namespace std;
typedef unsigned int u32;

// a b c 
// 0 0 0   []
// 1 0 0   [a]	
// 0 1 0   [b]
// 1 1 0   [ab]
// 0 0 1   [c]
// 1 0 1   [ac]
// 0 1 1   [bc]
// 1 1 1   [abc]

int ctoi(char c)
{
	return c -'0';
}

void find_max_subset_summed_pair(string s)
{
	typedef	map<int,string> SumMap; 
	SumMap summap;
	int biggestSum = 0;
	string biggestSubset;

	u32 mask = 0;
	for(int i =0; i < s.size(); ++i)
		mask |= 1 << i;

	while(mask)	
	{
		string subset;
		int sum = 0;	
		for(int j = 0; j < s.size(); j++)
		{
			if(mask & (1 << j))
			{
				subset += s[j];
				sum += ctoi(s[j]);
			}
		}
		pair<SumMap::iterator,bool> ret = summap.insert(make_pair(sum,subset));
		if(!ret.second && sum > biggestSum)
		{
			biggestSum = sum;
			biggestSubset = subset;
		}	
		--mask;
	}				
	cout << "Biggest subset is ";
	for(int i = 0; i < biggestSubset.size(); i++)
		cout << biggestSubset[i] << (i+1 == biggestSubset.size() ? "=" : "+");
		
	biggestSubset = summap[biggestSum];

	for(int i = 0; i < biggestSubset.size(); i++)
		cout << biggestSubset[i] << (i+1 == biggestSubset.size() ? "" : "+");
	cout << endl;
}
  
void print_subset_mask(string s)
{
	u32 mask = 0;
	for(int i =0; i < s.size(); ++i)
		mask |= 1 << i;

	while(mask)	
	{
		cout << "[";
		for(int j = 0; j < s.size(); j++)
			if(mask & (1 << j))
				cout << s[j];
		
		cout << "]" << endl;
		--mask;
	}				
	cout << "[]" << endl;
}

void print_subsets(string prefix, string rest)
{
	// subsets of "abc"	 Rest Prefix  Depth
	// []				  abc   -	
	// [a]				  bc    a
	// [b]				  ac    b
	// [c]				  ab	c
	// [ab]				  c		ab   
	// [ac]				  b		ac	  
	// [bc]				  a     bc     
	// [abc]			  -     abc    0 

	//cout << setw(10) << "prefix:" << prefix;
	//cout << setw(10) << "rest:" << rest << endl;

	cout << prefix << endl;
	if(!rest.size())
	{
		//cout << prefix << endl;
		return;
	}
	else
	{
		for(int i = 0; i < rest.size(); i++)
		{
			string p = prefix + rest.substr(i,1);				// add current c to current prefix.
			string r;

			for(int j = 0;j < rest.size(); j++)
				if(j != i)
					r+= rest[j];
		
			//cout << setw(10) << "prefix:" << p;
			//cout << setw(10) << "rest:" << r << endl;

			print_subsets(p,r);
		}
	}
}

int main(int argc, char** argv)
{
	if(argc <=1)
		cout << "please provide string to generate subsets of" << endl;

	string str(argv[1]);
	print_subsets(string(),str);
	//print_subset_mask(str);
	//find_max_subset_summed_pair(str);
	return 0;
}
