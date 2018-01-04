#include <iostream>
#include <cstddef>

template<std::size_t N>
struct Fibonachi
{
    static const std::size_t fib = Fibonachi<N - 1>::fib + Fibonachi<N - 2>::fib;
};

template<>
struct Fibonachi<0>
{
    static const std::size_t fib = 0;
};

template<>
struct Fibonachi<1>
{
    static const std::size_t fib = 1;
};


int main()
{
    Fibonachi<10> nadav;
    
    std::cout << nadav.fib << std::endl;
    
    return 0;
}
