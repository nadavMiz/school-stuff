#include "vectorSearchTable.h"

#include <algorithm> //find_if
#include <tr1/functional> //tr1::bind

namespace smartCampus
{

using namespace std::tr1::placeholders;

std::size_t VectorSearchTable::Remove(const Query& _query)
{
	std::size_t count = 0;
	
	std::vector<Query>::iterator itr = m_values.begin();
	while(m_values.end() != (itr = std::find_if(itr, m_values.end(), std::tr1::bind(CompareQueries, _query, _1))))
	{
		itr = m_values.erase(itr);
		++count;
	}
	
	return count;
}

bool VectorSearchTable::ExactRemove(const Query& _query)
{
	std::vector<Query>::iterator itr = std::find(m_values.begin(), m_values.end(), _query);
	if(m_values.end() != itr)
	{
		m_values.erase(itr);
		return true;
	}
	
	return false;
}

bool VectorSearchTable::IsPresent(const Query& _query) const
{
	std::vector<Query>::const_iterator itr = m_values.begin();
	itr = std::find_if(itr, m_values.end(), std::tr1::bind(CompareQueries, _1, _query));
	
	return m_values.end() != itr;
}

}
