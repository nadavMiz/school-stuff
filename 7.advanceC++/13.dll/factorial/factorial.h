#ifndef __FACTORIAL__
#define __FACTORIAL__

#include <cstddef>

#ifdef MY_FACTORIAL_DLL_EXPORTS
#define MY_FACTORIAL_DLL_API _declspec(dllexport)
#else
#define MY_FACTORIAL_DLL_API _declspec(dllimport)
#endif /* MY_FACTORIAL_DLL_EXPORTS */



std::size_t MY_FACTORIAL_DLL_API Factorial(std::size_t _n);

#endif /* __FACTORIAL__ */