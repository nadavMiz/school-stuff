#include <algorithm>
#include <tr1/functional>

#include "vectorRegistrationTable.h"

namespace smartCampus
{

using namespace std::tr1::placeholders;

bool VectorRegistrationTable::IsExist(Agent* _agent, const Query& _query) const
{
	return m_table.end() != std::find(m_table.begin(), m_table.end(), std::pair<Query, Agent*>(_query, _agent));
}

void VectorRegistrationTable::Insert(Agent* _agent, const Query& _query)
{
	if(IsExist(_agent, _query))
	{
		throw std::runtime_error("already exist");
	}
	
	m_table.push_back(std::pair<Query, Agent*>(_query, _agent));
}

bool VectorRegistrationTable::Remove(Agent* _agent, const Query& _query)
{
	std::vector<std::pair<Query, Agent*> >::iterator pair = std::find(m_table.begin(), m_table.end(), std::pair<Query, Agent*>(_query, _agent));
	if(m_table.end() == pair)
	{
		return false;
	}
	
	m_table.erase(pair);
	
	return true;
}

std::vector<Agent*> VectorRegistrationTable::Find(const Query& _query) const
{
	std::vector<Agent*> result;
	std::tr1::function<bool(const std::pair<Query, Agent*>&)> predicate = std::tr1::bind(CompareQueryToPair, _1, _query);
	std::vector<std::pair<Query, Agent*> >::const_iterator itr = m_table.begin();
	std::vector<std::pair<Query, Agent*> >::const_iterator end = m_table.end();
	
	while(end != (itr = std::find_if(itr, end, predicate)))
	{
		result.push_back(itr->second);
		++itr;
	}
	
	return result;
}

}
