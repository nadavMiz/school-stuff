// doFactorial.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stddef.h>
#include <iostream>

#include "factorial.h"

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "enter number to claculate factorial of" << std::endl;
	std::size_t a;
	std::cin >> a;
	std::cout << Factorial(a) << std::endl;
	std::cin >> a;
	return 0;
}

