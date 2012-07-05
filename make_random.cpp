#include <iostream>
#include <sstream>
#include <stdlib.h>

int main(int argc, char** argv)
{
	using namespace std;
	srand(time(NULL));

	if( argc <=1 )
	{
		cerr << "n-vals (max) (min)" << endl;
		return -1;
	}

	int count = 1;
	stringstream(argv[1]) >> count;
	
	int max_val = 65535;
	int min_val = 0;

	if( argc >2 )
		stringstream(argv[2]) >> min_val;

	if( argc >3 )
		stringstream(argv[3]) >> max_val;

	for(int i = 0; i < count; ++i)
	{
		int r = min_val + rand() % (max_val-min_val);
		cout << r << endl;
	}
}


