#ifndef TREE_SEARCH_TABLE_H
#define TREE_SEARCH_TABLE_H

#include <vector>
#include <map>
#include <string>
#include <sstream>

#include "uncopyable.h"
#include "query.h"

namespace smartCampus
{

template <class T>
class TreeSearchTable: public ISearchTable
{

public:
	//TreeSearchTable(); default CTOR
	virtual ~TreeSearchTable(){}
	
	virtual void Insert(const Query& _query, T _value);
	virtual void Remove(const Query& _query);
	virtual SearchTableItr Find(const Query& _query);
	virtual SearchTableItr Begin();
	virtual SearchTableItr End();

private:
	std::sstream& GetQueryStream(const Query& _query) const;

private:
	/* data */
	Node<std::string, Node<int, LeafNode> > m_table;
};

inline std::stringstream& TreeSearchTable::GeQuerytStream(const Query& _query) const
{
	stringstream stream;
	stream << _query.m_topic << _query.m_floor;
	return stream;
}

}
#endif /* SEARCH_TABLE_H */

