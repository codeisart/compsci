#include <iostream>
#include <string>

void removeDuplicates(char* s)
{
	for(char* i = s; *i; ++i)
	{
		for(char* j = i+1; *j; )
		{
			// Duplicate?
			if(*j == *i)
			{
				// Remove	
				char* k = j;
				for( ;*k; ++k)
					*k = *(k+1);

				// Terminate.
				*(k-1) = 0;
			}
			else
				j++;
		}	
	}
}

int main(int argc, char** argv)
{
	if(argc<=1)
	{
		std::cout << "please provide string to process" << std::endl;
		return 0;
	}

	std::string s(argv[1]);
	
	// Remove duplicates out of our string.
	removeDuplicates(&s[0]);

	std::cout << s << std::endl;

	return 0;
}
