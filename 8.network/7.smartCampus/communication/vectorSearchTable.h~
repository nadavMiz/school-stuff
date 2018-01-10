#ifndef __VECTOR_SEARCH_TABLE_H__
#define __VECTOR_SEARCH_TABLE_H__

#include <algorithm> //find_if
#include <vector>
#include <map> // std::pair
#include <string>
#include <cstring>

#include "isearchTable.h"
#include "query.h"

namespace smartCampus
{

template <class T>
class VectorSearchTable: public ISearchTable<T>
{
public:
	//VectorSearchTable();
	//virtual ~VectorSearchTable();
	virtual void Insert(const Query& _query, const T& _value);
	virtual void Remove(const T& _value);
	virtual void Remove(const Query& _query);
	virtual void Clear();
	virtual std::vector<T>& Find(const Query& _query) const;
	virtual bool IsPresent(const Query& _query) const;

private:
	/* data */
	std::vector<std::pair<Query, T> > m_values;
	mutable std::vector<T> m_results;
	
	static bool CompareQueries(const Query& _first, const Query& _second);
	static bool CompareQuerieValues(const std::string& _a, const std::string& _b);
	
	struct ComparePairToValue
	{
		ComparePairToValue(const T& _value): m_value(_value){}
		
		bool operator()(const std::pair<Query, T>& _pair){return _pair.second == m_value;}
		const T& m_value;
	};
	
	struct ComparePairToQuery
	{
		ComparePairToQuery(const Query& _query): m_query(_query){}
		
		bool operator()(const std::pair<Query, T>& _pair){return CompareQueries(_pair.first, m_query);}
		const Query& m_query;
	};
};

template <class T>
inline bool VectorSearchTable<T>::CompareQueries(const Query& _first, const Query& _second)
{
	return (_first.m_topic == _second.m_topic && CompareQuerieValues(_first.m_room, _second.m_room) && CompareQuerieValues(_first.m_floor, _second.m_floor));
}

template <class T>
inline bool VectorSearchTable<T>::CompareQuerieValues(const std::string& _a, const std::string& _b)
{
	return (_a == "ALL" || _b == "ALL" || _a == _b);
}

template <class T>
void VectorSearchTable<T>::Insert(const Query& _query, const T& _value)
{
	m_values.push_back(std::pair<Query, T>(_query, _value));
}

template <class T>
void VectorSearchTable<T>::Remove(const T& _value)
{
	typename std::vector<std::pair<Query, T> >::iterator itr = m_values.begin();
	
	if(m_values.end() != (itr = std::find_if(itr, m_values.end(), ComparePairToValue(_value))))
	{
		m_values.erase(itr);
	}
}

template <class T>
void VectorSearchTable<T>::Remove(const Query& _query)
{
	typename std::vector<std::pair<Query, T> >::iterator itr = m_values.begin();
	ComparePairToQuery predicate(_query);
	
	while(m_values.end() != (itr = std::find_if(itr, m_values.end(), predicate)))
	{
		itr = m_values.erase(itr);
	}
}

template <class T>
inline void VectorSearchTable<T>::Clear()
{
	m_values.clear();
}

template <class T>
std::vector<T>& VectorSearchTable<T>::Find(const Query& _query) const
{
	m_results.clear();

	typename std::vector<std::pair<Query, T> >::const_iterator itr = m_values.begin();
	ComparePairToQuery predicate(_query);
	
	while(m_values.end() != (itr = std::find_if(itr, m_values.end(), predicate)))
	{
		m_results.push_back(itr->second);
		++itr;
	}
	
	return m_results;
}

template <class T>
bool VectorSearchTable<T>::IsPresent(const Query& _query) const
{
	typename std::vector<std::pair<Query, T> >::const_iterator itr = m_values.begin();
	itr = std::find_if(itr, m_values.end(), ComparePairToQuery(_query));
	
	return m_values.end() != itr;
}

}
#endif /* __VECTOR_SEARCH_TABLE_H__ */

