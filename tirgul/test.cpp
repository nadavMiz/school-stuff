
#include <iostream>
#include <vector>

template <class T>
class ref
{
public:
	ref(T& _a): m_a(&_a){}
	operator T&() {return *m_a;}
	T* m_a;
};

int main()
{
	std::vector<ref<int> > vec;
	
	int* a = new int(5);
	
	int& b = *a;
	
	delete a;
	
	std::cout << *a << std::endl;
	std::cout << b << std::endl;
}

