#include "exception.h"

#include <iostream>

using namespace std;

void AmIRight(bool _isRight)
{
	if(!_isRight)
	{
		throw TException_t<int>(1, "you are not right", __FILE__, __LINE__);
	}
}

int main()
{
	try
	{
		AmIRight(false);
	}
	catch(TException_t<int> _err)
	{
		cout << _err.GetObject() << ": " << _err.GetMsg() << " file: " 
			 << _err.GetFileName() << " line: " << _err.GetLineNum() << endl;
	}
	return 1;
}
