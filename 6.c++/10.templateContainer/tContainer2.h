#ifndef __tContainer2_H__
#define __tContainer2_H__
//
#include <algorithm>    // std::find_if
#include <vector>       
#include <list>   
#include <typeinfo>     // typeid      

using namespace std; 


template <class T,template<class,class = allocator<T> > class Container>
class tContainer2_t
{
	typedef typename Container<T*>::iterator Itr;
	typedef typename Container<T*>::const_iterator ConstItr;

	public:
		tContainer2_t(){};
		~tContainer2_t (){};
		
		bool IsEmpty() const;
		unsigned int Size() const;
		void PushBack(const T* _val);
		T* GetLastElem() const;
		T* GetFirstElem() const;
		T* Find(const T& _val) const;
		T* Remove(const T& _val);
		void RemoveAll();
		bool RemoveAndDelete(const T& _val);
		void RemoveAndDeleteAll();
		T* operator[](unsigned int _index) const;
		

	private:
		/* data */
		Container<T*> m_container;
		
	private:
		struct MatchValue
		{
			MatchValue(const T& _toMatch): m_toMatch(_toMatch){}
			
			bool operator()(T* _val){return (m_toMatch == *_val);}
			
			private:
				T m_toMatch;
		};
		
	private:
		tContainer2_t(const tContainer2_t& _tcontainer);
		tContainer2_t& operator=(const tContainer2_t& _tcontainer);
};

/*--------------------------------------------------*/

template <typename T, template<class,class Alloc = allocator<T> > class Container>
bool tContainer2_t<T,Container>::IsEmpty() const
{
	return (0 == m_container.size());
}

/*--------------------------------------------------*/

template <typename T, template<class,class Alloc = allocator<T> > class Container>
unsigned int tContainer2_t<T,Container>::Size() const
{
	return m_container.size();
}

/*--------------------------------------------------*/

template <typename T, template<class,class Alloc = allocator<T> > class Container>
void tContainer2_t<T,Container>::PushBack(const T* _val)
{
	m_container.push_back((T*)_val);
}

/*--------------------------------------------------*/

template <typename T, template<class,class Alloc = allocator<T> > class Container>
T* tContainer2_t<T,Container>::GetLastElem() const
{
	if(IsEmpty())
	{
		return 0;
	}
	
	return *(--m_container.end());
}

/*--------------------------------------------------*/

template <typename T, template<class,class Alloc = allocator<T> > class Container>
T* tContainer2_t<T,Container>::GetFirstElem() const
{
	if(IsEmpty())
	{
		return 0;
	}
	
	return *(m_container.begin());
}

/*--------------------------------------------------*/

template <typename T, template<class,class Alloc = allocator<T> > class Container>
T* tContainer2_t<T,Container>::Find(const T& _val) const
{
	ConstItr result = find_if(m_container.begin(), m_container.end(), MatchValue(_val));	
	
	if(m_container.end() == result)
	{
		return 0;
	}
	
	return (T*)*result;
}

/*--------------------------------------------------*/

template <typename T, template<class,class Alloc = allocator<T> > class Container>
T* tContainer2_t<T,Container>::Remove(const T& _val)
{
	Itr toRemove = find_if(m_container.begin(), m_container.end(), MatchValue(_val));
	
	if(m_container.end() == toRemove)
	{
		return 0;
	}
	
	T* retval = *toRemove;
	
	m_container.erase(toRemove);
	
	return retval;
}

/*--------------------------------------------------*/

template <typename T, template<class,class Alloc = allocator<T> > class Container>
void tContainer2_t<T,Container>::RemoveAll()
{
	m_container.clear();
}

/*--------------------------------------------------*/

template <typename T, template<class,class Alloc = allocator<T> > class Container>
bool tContainer2_t<T,Container>::RemoveAndDelete(const T& _val)
{
	T* val = Remove(_val);
	
	if(val == 0)
	{
		return false;
	}
	
	delete val;
	return true;
}

/*--------------------------------------------------*/

template <typename T, template<class,class Alloc = allocator<T> > class Container>
void tContainer2_t<T,Container>::RemoveAndDeleteAll()
{
	for(Itr ValItr = m_container.begin(); ValItr != m_container.end(); ++ValItr)
	{
		delete (*ValItr);
	}
	
	m_container.clear();
}

/*--------------------------------------------------*/

template <typename T, template<class,class Alloc = allocator<T> > class Container>
T* tContainer2_t<T,Container>::operator[](unsigned int _index) const
{
	if(_index >= Size())
	{
		return 0;
	}
	
	if(typeid(vector<T*>) == typeid(m_container))
	{
		return ((vector<T*>*)&m_container)->at(_index);
	}
	else
	{
		ConstItr itr = m_container.begin();
		
		for(unsigned int i = 0; i < _index; ++i)
		{
			++itr;
		}
		return *itr;
	}
}


#endif /* __tContainer2_H__ */

