#ifndef SEARCH_TABLE_H
#define SEARCH_TABLE_H

#include <vector>
#include <map>
#include <string>
#include <sstream>

#include "uncopyable.h"
#include "query.h"

namespace smartCampus
{

template <class T>
class SearchTable: private Uncopyable
{
typedef std::map<std::string, std::multimap<int, T> > searchTable_t;

public:
	class iterator
	{
	public:
		T& operator*();
		T& operator->();
		void operator++();
		void operator--();
		
	private:
		LeafNode& GetNode();
	};

public:
	//SearchTable(); default CTOR
	//~SearchTable(); default DTOR
	void Insert(const Query& _query, T _value);
	void Remove(iterator& _itr);
	iterator Find(const Query& _query);
	iterator Begin();
	iterator End();

private:
	std::sstream& GeQuerytStream(const Query& _query) const;

private:
	template <class Key, class Value>
	class Node
	{
	public:
		Node(std::string _type);
		void Insert(std::stringstream& _query, T _value);
		void Remove(Value _value);
		iterator Find(std::stringstream& _query);
		
	private:
		std::map<Key, Value> m_map;
		Node m_parent;
	};
	
private:
	class LeafNode
	{
		public:
		Node(std::string _type);
		void Insert(const Query& _query, T _value);
		void Remove(Value _value);
		T& GetData();
		
	private:
		T m_data;
		Node m_parent;
	};

private:
	/* data */
	Node<std::string, Node<int, LeafNode> > m_table;
	std::vector<std::multimap<int, T>::iterator > m_results;
};

inline std::stringstream& SearchTable::GeQuerytStream(const Query& _query) const
{
	stringstream stream;
	stream << _query.m_topic << _query.m_floor;
	return stream;
}

}
#endif /* SEARCH_TABLE_H */

