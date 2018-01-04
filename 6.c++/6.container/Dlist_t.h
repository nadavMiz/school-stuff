#ifndef __DLIST_T_H__
#define __DLIST_T_H__

template <class T>
class DList: public container_t<T>
{
	public:
		DList ();
		DList(const DList<T>& _list);
		virtual ~DList ();
		
		//size_t Count() const;
		//bool IsEmpty() const;
		
		DList<T>& operator=(const DList<T>& _list);
		/*virtual functions*/
		virtual bool Append(size_t _index, const T* _item);
		virtual bool Prepend(size_t _index, const T* _item);
		virtual bool Contains(const T& _item) const;
		virtual T* Find(const T& _item) const;
		virtual bool Insert(const T* _item);
		virtual int Index(const T& _item) const;
		virtual T* Remove(const T& _item);
		virtual void RemoveAll();
		virtual bool RemoveAndDelete(const T& _item); // false if item not found
		virtual void RemoveAndDeleteAll();

	private:
		class Node
		{
			public:
				Node(T* _data);
				Node(const Node& _node);
				~Node();
				
				Node& operator=(const Node& _node);
				Node* Detach();
				bool AddNext(const T* _item);
				
			public:
				/*data*/
				T* m_data;
				Node* m_next;
				Node* m_prev;
		};

	private:
		/* data */
		Node m_head;
		Node m_tail;
	
	private:
		Node* GetNode(size_t _index) const;
		Node* GetNode(const T& _item) const;
	
};

/*--------------------node nested class--------------------*/

template <class T>
DList<T>::Node::Node(T* _data)
{
	m_data = _data;
	m_next = 0;
	m_prev = 0;
}

template <class T>
DList<T>::Node::Node(const Node& _node)
{
	m_data = _node.m_data;
	m_next = 0;
	m_prev = 0;
}

template <class T>
typename DList<T>::Node& DList<T>::Node::operator=(const Node& _node)
{
	m_data = _node.m_data;
	
	return *this;
}

template <class T>
DList<T>::Node::~Node(){}

template <class T>
typename DList<T>::Node* DList<T>::Node::Detach()
{
	m_prev->m_next = m_next;
	m_next->m_prev = m_prev;
}

template <class T>
bool DList<T>::Node::AddNext(const T* _data)
{
	Node* node = new Node((T*)_data);
	if(0 == node)
	{
		return false;
	}

	m_next->m_prev = node;
	node->m_next = m_next;
	node->m_prev = this;
	m_next = node;
	
	return true;
}

/*----------------------linked list----------------------------*/

template <class T>
DList<T>::DList(): m_head(0), m_tail(0)
{
	m_head.m_next = &m_tail;
	m_tail.m_prev = &m_head;
	this->m_numberOfItems = 0;
}

template <class T>
DList<T>::DList(const DList<T>& _list)
{
	m_head.m_next = &m_tail;
	m_tail.m_prev = &m_head;
	Node* newNode;
	Node* copyNode = &(_list.m_head);
	
	for(size_t i = 0; i < _list.m_numberOfItems; ++i)
	{
		newNode = new Node(&copyNode);
		if(0 == newNode)
		{
			//TODO something
		}
		m_tail.AddPrev(newNode);
	}
	
	this->m_numberOfItems = _list.m_numberOfItems;
}

/*------------------------------------------------------*/

template <class T>
DList<T>::~DList ()
{
	RemoveAll();
}

/*------------------------------------------------------*/

template <class T>
DList<T>& DList<T>::operator=(const DList<T>& _list)
{
	RemoveAll();
	
	Node* newNode;
	Node* copyNode = &(_list.m_head);
	
	for(size_t i = 0; i < _list.m_numberOfItems; ++i)
	{
		newNode = new Node(&copyNode);
		if(0 == newNode)
		{
			//TODO something
		}
		m_tail.AddPrev(newNode);
	}
	
	this->m_numberOfItems = _list.m_numberOfItems;
}

/*--------------------------------------------------------*/

template <class T>
typename DList<T>::Node* DList<T>::GetNode(size_t _index) const
{
	if(this->m_numberOfItems < _index)
	{
		return 0;
	}
	
	Node* current = (Node*)&m_head;
	for(size_t i = 0; i < _index; ++i)
	{
		current = current->m_next;
	}
	
	return current;
}

/*--------------------------------------------------------*/

template <class T>
typename DList<T>::Node* DList<T>::GetNode(const T& _item) const
{
	Node* current = m_head.m_next;
	while(current != &m_tail)
	{
		if(*(current->m_data) == _item)
		{
			return current;
		}
		
		current = current->m_next;
	}
	
	return 0;
}

/*--------------------------------------------------------*/

template <class T>
bool DList<T>::Append(size_t _index, const T* _item)
{
	if(_index >= this->m_numberOfItems)
	{
		return false;
	}

	if(GetNode(_index)->AddNext(_item))
	{
		++this->m_numberOfItems;
		return true;
	}
}

/*--------------------------------------------------------*/

template <class T>
bool DList<T>::Prepend(size_t _index, const T* _item)
{
	if(_index >= this->m_numberOfItems)
	{
		return false;
	}

	if(GetNode(_index)->m_prev->AddNext(_item))
	{
		++this->m_numberOfItems;
		return true;
	}
	
	return false;
}

/*-----------------------------------------------------------*/

template <class T>
bool DList<T>::Insert(const T* _item)
{
	if(m_tail.m_prev->AddNext(_item))
	{
		++this->m_numberOfItems;
		return true;
	}
	return false;
}

/*--------------------------------------------------------*/

template <class T>
bool DList<T>::Contains(const T& _item) const
{
	return (0 != GetNode(_item));
}

/*--------------------------------------------------------*/

template <class T>
T* DList<T>::Find(const T& _item) const
{
	Node* itemsNode = GetNode(_item);
	if(0 == itemsNode)
	{
		return 0;
	}
	
	return itemsNode->m_data;
}

/*------------------------------------------------------------*/

template <class T>
int DList<T>::Index(const T& _item) const
{
	Node* current = m_head.m_next;
	int i = 0;
	
	while(current != &m_tail)
	{
		if(*(current->m_data) == _item)
		{
			return i;
		}
		
		current = current->m_next;
		++i;
	}
	
	return -1;
}

/*-------------------------------------------------------------*/

template <class T>
T* DList<T>::Remove(const T& _item)
{
	Node* itemsNode = GetNode(_item);
	if(0 == itemsNode)
	{
		return 0;
	}
	
	T* data = itemsNode->m_data;
	itemsNode->Detach();
	delete itemsNode;
	
	return data;
}

/*---------------------------------------------------------------*/

template <class T>
void DList<T>::RemoveAll()
{
	Node* currentNode = m_head.m_next;
	Node* nextNode;

	while(currentNode != &m_tail)
	{
		nextNode = currentNode->m_next;
		delete currentNode;
		currentNode = nextNode;
	}	
}

/*----------------------------------------------------------------*/

template <class T>
bool DList<T>::RemoveAndDelete(const T& _item)
{
	T* data = Remove(_item);
	if(0 == data)
	{
		return false;
	}
	
	delete data;
	return true;
}

/*-----------------------------------------------------------------*/

template <class T>
void DList<T>::RemoveAndDeleteAll()
{
	Node* currentNode = m_head.m_next;
	Node* nextNode;

	while(currentNode != &m_tail)
	{
		nextNode = currentNode->m_next;
		delete currentNode->m_data;
		delete currentNode;
		currentNode = nextNode;
	}	
}

#endif /* __DLIST_T_H__ */

