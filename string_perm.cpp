#include <iostream>
#include <sstream>
#include <string>

void printStringPerm(std::string& s,int permIndex)
{
	using namespace std;

	if(permIndex == s.length()-1)
	{
		cout << s << endl;
		return;
	}
	
	printStringPerm(s,permIndex+1);
	
	for(int i = permIndex+1; i < s.length(); ++i)
	{
		std::swap(s[i], s[permIndex]);
		printStringPerm(s,permIndex+1);
	}
}

int main(int argc, char** argv)
{
	using namespace std;
	if(argc <=1)
	{
		std::cout << "please supply string to permutate" << endl;
		return 0;
	}

	string s(argv[1]);

	printStringPerm(s,0);

	return 0;
}
