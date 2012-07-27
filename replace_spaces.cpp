#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int len(const char* s)
{
	int i = 0;
	for( ; s[i]; i++ );
	return i;
}

void replace_string(char* s, char c, char* insertString)
{
	// Find out how big the new string is.
	int insertLength = len(insertString);
	int ourLength = len(s);
	
	// Loop to end up string looking at each char. (string is growing in length as we interate)
	for(char* i = s; *i; i++)
	{
		if(*i == c)
		{
			// Move everything above up by the length of new string, minus the length of the char, i.e. 1.
			int offset = insertLength-1;
			for(char* j = s+ourLength+offset; j != i; j--)
			{
				char* src = j-offset;
				*j = *src;
			}

			// Insert the string at position. i.
			for(int j = 0; j < insertLength; ++j)
				i[j] = insertString[j];

			// Increase out length
			ourLength+=offset;
		}
	}
}

int main(int argc, char** argv)
{
	if(argc <=3)
	{
		std::cout << "please supply a string to mangle, character to replace and then what with"<< std::endl;
		return 0;
	}
	
	string s(argv[1]);
	string c(argv[2]);
	string ins(argv[3]);
	
	s.resize(s.size() * (ins.size()-1));

	replace_string(&s[0],c[0],&ins[0]);

	cout << s << endl;

	return 0;
}
