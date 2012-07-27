#include <iostream>
#include <string>

bool isAnagram(const char* a, const char* b)
{
	char statsA[256] = {0};
	char statsB[256] = {0};

	while(*a)
		statsA[*a++]++;

	while(*b)
		statsB[*b++]++;
	
	for(int i = 0; i < 256; ++i)
		if(statsA[i] != statsB[i])
			return false;

	return true;
}

int main(int argc, char** argv)
{
	if(argc <=2)
	{
		std::cout << "please supply 2 strings" << std::endl;
		return 0;
	}

	if( isAnagram(argv[1], argv[2]) )
		std::cout << "YES they are anagrams" << std::endl;
	else
		std::cout << "no they are not anagrams" << std::endl;

	return 0;
}
