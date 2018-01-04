// factorial.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <cstddef>

#define MY_FACTORIAL_DLL_EXPORTS
#include "factorial.h"

std::size_t Factorial(std::size_t _n)
{
	if(0 == _n)
	{
		return 1;
	}

	return _n * Factorial(_n - 1);
}