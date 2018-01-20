#ifndef __MULTI_KEY_SEARCH_TREE_H__
#define __MULTI_KEY_SEARCH_TREE_H__

#include <tr1/memory>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>

#include "query.h"

namespace smartCampus
{

template<class T>
class MultiKeySearchTree
{

public:
	//MultiKeySearchTree();
	//~MultiKeySearchTree();
	inline void Insert(std::stringstream& _query, const T& _value);
	inline void Remove(const T& _value);
	inline void Remove(std::stringstream& _query);
	inline std::vector<T>& Find(std::stringstream& _query);
	inline void Clear();

private:
	class Component
	{
	friend class MultiKeySearchTree::Node;
	friend class MultiKeySearchTree::Leaf;
	
	public:
		virtual ~Component(){}
		virtual void Insert(std::stringstream& _query, const T& _value) = 0;
		virtual void Remove(const T& _value) = 0;
		virtual void Remove(std::stringstream& _query) = 0;
		virtual void Find(std::stringstream&, std::vector<T>& _vec) const = 0;
		virtual void Clear() = 0;
		virtual bool IsEmpty() = 0;
	};
	
private:
	template<class Value>
	class Node: public MultiKeySearchTree::Component
	{
	typedef typename std::map<std::string, std::tr1::shared_ptr<Value> > map_t;
	
	public:
		//virtual ~Node(){}
		virtual void Insert(std::stringstream& _query, const T& _value);
		virtual void Remove(const T& _value);
		virtual void Remove(std::stringstream& _query);
		virtual void Find(std::stringstream&, std::vector<T>& _vec) const;
		virtual void Clear();
		virtual bool IsEmpty();
		
	private:
		map_t m_values;
		
		template <class Context>
		void RemoveFromChild(typename map_t::iterator _value, Context _context);
	};
	
private:
	class LeafNode: public MultiKeySearchTree::Component
	{
		//virtual ~Node(){}
		virtual void Insert(std::stringstream& _query, const T& _value);
		virtual void Remove(const T& _value);
		virtual void Remove(std::stringstream& _query);
		virtual void Find(std::stringstream&, std::vector<T>& _vec) const;
		virtual void Clear();
		virtual bool IsEmpty();
		
	private:
		std::set<T> m_set;
	};
	
private:
	MultiKeySearchTree::Node< Node<LeafNode> > m_tree;
	std::vector<T> m_results;
};

/*-------------tree functions------------------------*/

template <class T>
inline void MultiKeySearchTree<T>::Insert(std::stringstream& _query, const T& _value)
{
	m_tree.Insert(_query, _value);
}

template <class T>
inline void MultiKeySearchTree<T>::Remove(const T& _value)
{
	m_tree.Remove(_value);
}

template <class T>
inline void MultiKeySearchTree<T>::Remove(std::stringstream& _query)
{
	m_tree.Remove(_query);
}

template <class T>
inline std::vector<T>& MultiKeySearchTree<T>::Find(std::stringstream& _query)
{
	m_tree.Find(_query, m_results);
	return m_results;
}

template <class T>
inline void MultiKeySearchTree<T>::Clear()
{
	m_tree.Clear();
}

/*------------------node functions*/

template <class T>
template<class Value>
void MultiKeySearchTree<T>::Node<Value>::Insert(std::stringstream& _query, const T& _value)
{
	std::string key;
	getline(_query, key, ' ');
	
	typename map_t::iterator itr = m_values.find(_query);
	if(itr != m_values.end())
	{
		(*itr)->Insert(_query, _value);
	}
	else
	{
		std::tr1::shared_ptr<Value> newNode(new Value);
		newNode->Insert(_query, _value);
		
		m_values.insert(std::pair<std::string, Value>(key, newNode));
	}
}

template <class T>
template<class Value>
template <class Context>
void MultiKeySearchTree<T>::Node<Value>::RemoveFromChild(typename map_t::iterator _value, Context _context)
{
	(*_value)->Remove(_context);
	
	if((*_value)->IsEmpty())
	{
		m_values.erase(_value);
	}
}

template <class T>
template<class Value>
void MultiKeySearchTree<T>::Node<Value>::Remove(const T& _value)
{
	for(typename map_t::iterator itr = m_values.begin(); itr != m_values.end(); ++itr)
	{
		RemoveFromChild(itr, _value);
	}
}

template <class T>
template<class Value>
void MultiKeySearchTree<T>::Node<Value>::Remove(std::stringstream& _query)
{
	std::string key;
	getline(_query, key, ' ');
	
	if("ALL" == key)
	{
		for(typename map_t::iterator itr = m_values.begin(); itr != m_values.end(); ++itr)
		{
			RemoveFromChild(itr, _query);
		}
	}
	
	typename map_t::iterator itr = m_values.find(_query);
	if(itr != m_values.end())
	{
		return;
	}
	
	RemoveFromChild(itr, _query);
}


template <class T>
template<class Value>
void MultiKeySearchTree<T>::Node<Value>::Find(std::stringstream& _query, std::vector<T>& _vec) const
{
	std::string key;
	getline(_query, key, ' ');
	
	if("ALL" == key)
	{
		for(typename map_t::iterator itr = m_values.begin(); itr != m_values.end(); ++itr)
		{
			(*itr)->Find(_query, _vec);
			return;
		}
	}
	
	typename std::map<std::string, Value>::iterator itr = m_values.find(_query);
	if(itr != m_values.end())
	{
		return;
	}
	
	(*itr)->Find(_query, _vec);
}

template <class T>
template<class Value>
void MultiKeySearchTree<T>::Node<Value>::Clear()
{
	m_values.clear();
}

/*leaf functions*/
template <class T>
void MultiKeySearchTree<T>::LeafNode::Insert(std::stringstream& _query, const T& _value)
{
	m_set.insert(_value);
}

template <class T>
void MultiKeySearchTree<T>::LeafNode::Remove(const T& _value)
{
	m_set.erase(_value);
}

template <class T>
void MultiKeySearchTree<T>::LeafNode::Remove(std::stringstream& _query)
{
	m_set.clear();
}

template <class T>
void MultiKeySearchTree<T>::LeafNode::Find(std::stringstream&, std::vector<T>& _vec) const
{
	_vec.insert(_vec.end(), m_set.begin(), m_set.end());
}

template <class T>
void MultiKeySearchTree<T>::LeafNode::Clear()
{
	m_set.clear();
}

}
#endif /* __MULTI_KEY_SEARCH_TREE_H__ */

