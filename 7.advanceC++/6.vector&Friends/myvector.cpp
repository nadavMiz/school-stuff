#include <vector>
#include <list>
#include <iostream>
#include <algorithm>

unsigned int Count(int _value)
{
    static int count = 0;
    ++count;
    
    return count;
}

int main()
{
    std::list<int> m_nadav;
    
    for(int i = 0; i < 5; ++i)
    {
        m_nadav.push_back(71070);
    }
    
    std::cout << for_each(m_nadav.begin(), m_nadav.end(), Count)(0) << std::endl;
    
    return 1;
}
