#include <iostream>

#include "parser.h"

using namespace std;

int main(int argc, char* argv[])
{
	
	parser_t qqParser;
	
	for(int i = 1; i < argc; ++i)
	{
		cout << "		" << argv[i] << endl;
		if(!qqParser.ParseFile(argv[i]))
		{
			cout << "	  coulnd't open file " << endl;
		}
		
		cout << endl;
	}
}
