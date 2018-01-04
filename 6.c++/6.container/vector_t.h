#ifndef __VECTOR_T_H__
#define __VECTOR_T_H__

#include "container_t.h"

template <class T>
class Vector_t: public container_t<T>
{
	public:
		Vector_t(size_t _capacity = m_defaultCapacity);
		Vector_t(const Vector_t<T>& _vector);
		virtual ~Vector_t();
		Vector_t<T>& operator=(const Vector_t<T>& _vector);
		// size_t Count() const;
		// bool IsEmpty() const;
		
		/*virtual functions*/
		virtual bool Append(size_t _index, const T* _item);
		virtual bool Prepend(size_t _index, const T* _item);
		virtual bool Contains(const T& _item) const;
		virtual T* Find(const T& _item) const;
		virtual bool Insert(const T* _item);
		virtual int Index(const T& _item) const;
		virtual T* Remove(const T& _item); // false if item not found
		virtual void RemoveAll();
		virtual bool RemoveAndDelete(const T& _item); // false if item not found
		virtual void RemoveAndDeleteAll();

	protected:
		// this->m_numberOfItems;

	private:
		/* data */
		size_t m_capacity;
		T** m_array;
		
		/* static data */
		static size_t m_defaultCapacity; //default to 32
		static size_t m_realocMultiplyer; //default to 2
	
	private:
		void CopyArray(T** _a, T** _b, size_t _numOfItems);
		bool RealocateVector(size_t _newCapacity); // won't copy items with index that exceeds _newCapacity
		bool ShiftRight(size_t _index); //also shifts the element at _index
		void ShiftLeft(size_t _index); //element at _index will be overwritten
};

/*---------------------------------------------*/

template <class T>
size_t Vector_t<T>::m_defaultCapacity = 32;

template <class T>
size_t Vector_t<T>::m_realocMultiplyer = 2;

/*---------------------------------------------*/

template <class T>
Vector_t<T>::Vector_t(size_t _capacity)
{
	m_array = new T*[_capacity];
	if(NULL == m_array)
	{
		//TODO something
	}
	
	m_capacity = _capacity;
	this->m_numberOfItems = 0;
}

/*----------------------------------------------*/

template <class T>
void Vector_t<T>::CopyArray(T** _a, T** _b, size_t _numOfItems)
{
	for(size_t i = 0; i < _numOfItems; ++i)
	{
		_a[i] = _b[i];
	}
}

/*----------------------------------------------*/

template <class T>
Vector_t<T>::Vector_t(const Vector_t<T>& _vector)
{	
	m_array = new T*[_vector.m_capacity];
	if(NULL == m_array)
	{
		//TODO something
	}
	
	CopyArray(m_array,_vector.m_array, _vector.m_numberOfItems);
	
	m_capacity = _vector.m_capacity;
	this->m_numberOfItems = _vector.m_numberOfItems;
}

/*---------------------------------------------*/

template <class T>
Vector_t<T>::~Vector_t()
{
	delete[] m_array;
}

/*-----------------------------------------------*/

template <class T>
Vector_t<T>& Vector_t<T>::operator=(const Vector_t<T>& _vector)
{
	// if the vector is not big enough increase its size
	if(_vector.m_numberOfItems > m_capacity)
	{
		delete[] m_array;
		m_array = new T*[_vector.m_capacity];
		if(NULL == m_array)
		{
			//TODO something
		}
		m_capacity = _vector.m_capacity;
	}
	
	CopyArray(m_array,_vector.m_array, _vector.m_numberOfItems);
	this->m_numberOfItems = _vector.m_numberOfItems;
}


/*------------------------------------------------*/

template <class T>
bool Vector_t<T>::RealocateVector(size_t _newCapacity)
{
	T** newVector = new T*[_newCapacity];
	if(NULL == newVector)
	{
		return false;
	}
	
	if(_newCapacity < this->m_numberOfItems)
	{
		this->m_numberOfItems = _newCapacity;
	}
	
	CopyArray(newVector, m_array, this->m_numberOfItems);
	m_capacity = _newCapacity;
	
	return true;
}

/*----------------------------------------------------*/

template <class T>
bool Vector_t<T>::ShiftRight(size_t _index)
{
	if(this->m_numberOfItems == m_capacity)
	{
		if(false == RealocateVector(m_capacity*m_realocMultiplyer))
		{
			return false;
		}
	}
	
	for(size_t i = this->m_numberOfItems - 1; i >= _index; --i)
	{
		m_array[i + 1] = m_array[i];
	}
	
	//for safety
	m_array[_index] = NULL;
	
	++this->m_numberOfItems;
	
	return true;
}

/*-----------------------------------------------------*/

template <class T>
void Vector_t<T>::ShiftLeft(size_t _index)
{
	for(size_t i = _index + 1; i < this->m_numberOfItems; ++i)
	{
		m_array[i - 1] = m_array[i];
	}
	
	--this->m_numberOfItems;
}

/*-----------------------------------------------------*/

template <class T>
bool Vector_t<T>::Prepend(size_t _index, const T* _item)
{
	if(NULL == _item || _index > this->m_numberOfItems)
	{
		return false;
	}
	
	if(false == ShiftRight(_index))
	{
		return false;
	}
	
	m_array[_index] = (T*)_item;
	
	return true;
}

/*-----------------------------------------------------*/

template <class T>
bool Vector_t<T>::Append(size_t _index, const T* _item)
{
	return Prepend(_index + 1, _item);
}

/*----------------------------------------------------*/

template <class T>
int Vector_t<T>::Index(const T& _item) const
{
	for(size_t i = 0; i < this->m_numberOfItems; ++i)
	{
		if(_item == *(m_array[i]))
		{
			return i;
		}
	}
	
	return -1;
}

/*---------------------------------------------------*/

template <class T>
bool Vector_t<T>::Contains(const T& _item) const
{
	return (-1 != Index(_item));
}

/*-----------------------------------------------------*/

template <class T>
T* Vector_t<T>::Find(const T& _item) const
{
	int index = Index(_item);
	
	if(-1 == index)
	{
		return NULL;
	}
	
	return m_array[index];
}

/*------------------------------------------------------*/

template <class T>
bool Vector_t<T>::Insert(const T* _item)
{
	if(this->m_numberOfItems == m_capacity)
	{
		if(false == RealocateVector(m_capacity*m_realocMultiplyer))
		{
			return false;
		}
	}
	
	m_array[this->m_numberOfItems] = (T*)_item;
	++this->m_numberOfItems;
	
	return true;
}

/*------------------------------------------------------*/

template <class T>
T* Vector_t<T>::Remove(const T& _item)
{
	int index = Index(_item);
	if(-1 == index)
	{
		return NULL;
	}
	
	T* item = m_array[index];
	
	ShiftLeft((size_t)index);
	
	return item;
}

/*------------------------------------------------------*/

template <class T>
void Vector_t<T>::RemoveAll()
{
	this->m_numberOfItems = 0;
}

/*-------------------------------------------------------*/

template <class T>
bool Vector_t<T>::RemoveAndDelete(const T& _item)
{
	T* item = Remove(_item);
	if(NULL == item)
	{
		return false;
	}
	
	delete item;
	
	return true;
}

/*--------------------------------------------------------*/

template <class T>
void Vector_t<T>::RemoveAndDeleteAll()
{
	for(size_t i = 0; i < this->m_numberOfItems; ++i)
	{
		delete m_array[i];
	}
	
	this->m_numberOfItems = 0;
}


#endif /* __VECTOR_T_H__ */

