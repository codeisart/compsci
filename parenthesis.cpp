#include <string>
#include <iostream>
#include <sstream>

using namespace std;

void printParenthesis(int leftRemain, int rightRemain, string str)
{
	if(!rightRemain)
	{
		cout << str << endl;
		return;
	}

	if(leftRemain > 0)
	{
		printParenthesis(leftRemain-1,rightRemain, str+"(" );
		if(leftRemain < rightRemain)
			printParenthesis(leftRemain,rightRemain-1, str+")" );
	}
	else
		printParenthesis(leftRemain,rightRemain-1, str+")" );
}

int main(int argc, char** argv)
{
	if(argc <=2)
	{
		cout << "#-left-brackets #-right-backtes" << endl;
		return -1;
	}

	int left, right;
	stringstream(argv[1]) >> left;
	stringstream(argv[2]) >> right;

	printParenthesis(left,right, "");
}
