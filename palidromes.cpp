#include <iostream>
#include <string>

using namespace std;

bool isPalidrome(string s)
{
	if(s.size() <= 1)
		return false;
	string c(s.rbegin(),s.rend());
	return s == c;
}

int main(int argc, char** argv)
{
	if(argc <=1)
	{
		cout << "please supply string to parse for palidromes." << endl;
		return 0;
	}
	string s(argv[1]);

	for(int i =0; i < s.size(); ++i)
	{
		string sub = s.substr(i);
		if(isPalidrome(sub))
			cout << sub << endl;
	}

	return 0;
}
