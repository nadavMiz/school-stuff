#include "treeRegistrationTable.h"
#include "vectorRegistrationTable.h"

namespace smartCampus
{

RegistrationTablePtr TreeRegistrationTable::AddRegistrationTable(const std::string& _topic)
{
	RegistrationTablePtr newTable(new VectorRegistrationTable);
	
	m_table.insert(std::pair<std::string, RegistrationTablePtr>(_topic, newTable));
	
	return newTable;
}

void TreeRegistrationTable::Insert(Agent* _agent, const Query& _query)
{
	RegistrationTablePtr table;
	
	// get the topics registration table if not exists create a new one
	std::map<std::string, RegistrationTablePtr>::iterator registrationTableItr = m_table.find(_query.m_topic);
	if(registrationTableItr != m_table.end())
	{
		table = registrationTableItr->second;
	}
	else
	{
		table = AddRegistrationTable(_query.m_topic);
	}
	
	try
	{
		table->Insert(_agent, _query);
	}
	// if new registration table was created but insertion failed: need to erase the new table to provide strong guarenty
	catch(const std::exception& _err)
	{
		if(table->Empty())
		{
			m_table.erase(_query.m_topic);
		}
		throw;
	}
}

bool TreeRegistrationTable::Remove(Agent* _agent, const Query& _query)
{
	std::map<std::string, RegistrationTablePtr>::iterator registrationTableItr = m_table.find(_query.m_topic);
	if(registrationTableItr == m_table.end())
	{
		return false;
	}
	
	bool isRemoved = registrationTableItr->second->Remove(_agent, _query);
	
	if(isRemoved && registrationTableItr->second->Empty())
	{
		m_table.erase(registrationTableItr);
	}
	
	return isRemoved;
}


std::vector<Agent*> TreeRegistrationTable::Find(const Event& _event) const
{
	std::map<std::string, RegistrationTablePtr>::const_iterator registrationTableItr = m_table.find(_event->m_topic);
	if(registrationTableItr == m_table.end())
	{
		return std::vector<Agent*>();
	}
	
	return registrationTableItr->second->Find(_event);
}

}
