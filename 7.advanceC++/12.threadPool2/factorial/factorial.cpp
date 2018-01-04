#include <iostream>
#include <cstddef>

std::size_t factorial(std::size_t _n)
{
    if(0 == _n)
    {
        return 1;
    } 
    return _n * factorial(_n - 1);
}


int main()
{
    std::cout << factorial(50) << std::endl;
    return 1;
}


