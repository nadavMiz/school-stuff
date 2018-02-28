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

bool CompareAgentToPair(const std::pair<Query, Agent*>& _pair, const Agent* _agent)
{
	return _pair.second == _agent;
}

bool VectorRegistrationTable::Remove(Agent* _agent)
{
	return (m_table.begin() == std::remove_if(m_table.begin(), m_table.end(), std::tr1::bind(CompareAgentToPair, _1, _agent)));
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

bool VectorRegistrationTable::CompareEventToPair(const std::pair<Query, Agent*>& _pair, const Event& _event)
{
	return (_pair.first.m_topic == _event->m_topic && CompareQuerieValues(_pair.first.m_room, _event->m_room) && CompareQuerieValues(_pair.first.m_floor, _event->m_floor));
}

std::vector<Agent*> VectorRegistrationTable::Find(const Event& _event) const
{
	std::vector<Agent*> result;
	std::tr1::function<bool(const std::pair<Query, Agent*>&)> predicate = std::tr1::bind(CompareEventToPair, _1, _event);
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
