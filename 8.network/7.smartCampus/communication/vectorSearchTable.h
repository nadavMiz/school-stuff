#ifndef __VECTOR_SEARCH_TABLE_H__
#define __VECTOR_SEARCH_TABLE_H__

#include <vector>
#include <string>

#include "isearchTable.h"
#include "query.h"

namespace smartCampus
{

class VectorSearchTable: public ISearchTable
{
public:
	//VectorSearchTable();
	//virtual ~VectorSearchTable();
	virtual void Insert(const Query& _query);
	virtual std::size_t Remove(const Query& _query);
	virtual bool ExactRemove(const Query& _query);
	virtual void Clear();
	virtual bool IsPresent(const Query& _query) const;
	virtual bool IsEmpty() const;

private:
	/* data */
	std::vector<Query> m_values;
	
	static bool CompareQueries(const Query& _first, const Query& _second);
	static bool CompareQuerieValues(const std::string& _a, const std::string& _b);
};

inline bool VectorSearchTable::CompareQueries(const Query& _first, const Query& _second)
{
	return (_first.m_topic == _second.m_topic && CompareQuerieValues(_first.m_room, _second.m_room) && CompareQuerieValues(_first.m_floor, _second.m_floor));
}

inline bool VectorSearchTable::CompareQuerieValues(const std::string& _a, const std::string& _b)
{
	return (_a == "ALL" || _b == "ALL" || _a == _b);
}

inline void VectorSearchTable::Insert(const Query& _query)
{
	m_values.push_back(_query);
}

inline void VectorSearchTable::Clear()
{
	m_values.clear();
}

inline bool VectorSearchTable::IsEmpty() const
{
	return m_values.empty();
}

}
#endif /* __VECTOR_SEARCH_TABLE_H__ */

