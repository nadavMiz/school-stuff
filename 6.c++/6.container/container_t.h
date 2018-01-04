#ifndef __CONTAINER_T_H__
#define __CONTAINER_T_H__

#include <stddef.h>

template <class T>
class container_t
{
	public:
		container_t (){};
		virtual ~container_t(){};
		
		size_t Count() const;
		bool IsEmpty() const;
		
		/*virtual functions*/
		virtual bool Append(size_t _index, const T* _item) = 0;
		virtual bool Prepend(size_t _index, const T* _item) = 0;
		virtual bool Contains(const T& _item) const = 0;
		virtual T* Find(const T& _item) const = 0;
		virtual bool Insert(const T* _item) = 0;
		virtual int Index(const T& _item) const = 0;
		virtual T* Remove(const T& _item) = 0; // false if item not found
		virtual void RemoveAll() = 0;
		virtual bool RemoveAndDelete(const T& _item) = 0; // false if item not found
		virtual void RemoveAndDeleteAll() = 0;

	protected:
		/* data */
		size_t m_numberOfItems;
};

template <class T>
size_t container_t<T>::Count() const
{
	return m_numberOfItems;
}

template <class T>
bool container_t<T>::IsEmpty() const
{
	return (0 == m_numberOfItems);
}

#endif /* __CONTAINER_T_H__ */

