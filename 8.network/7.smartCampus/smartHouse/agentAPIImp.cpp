#include "agentAPIImp.h"

namespace smartCampus
{

AgentAPIIMP::AgentAPIIMP(Hub* _hub, Communicator* _communicator):
	m_hub(_hub)
,	m_communicator(_communicator)
{}

void AgentAPIIMP::Subscribe(Agent* _agent, const smartCampus::Query& _query)
{
	_hub->Subscribe(_agent, _query);
}

void AgentAPIIMP::Subscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName)
{
	m_hub->Subscribe(_agent, _query, _sectionName);
	
	try
	{
		m_communicator->Subscribe(_agent, _query, _sectionName);
	}
	catch(const std::exception& _err)
	{
		m_hub->Unsubscribe(Agent* _agent, _query, _sectionName);
		throw;
	}
}

void AgentAPIIMP::Unsubscribe(Agent* _agent, const smartCampus::Query& _query)
{
	m_hub->Unsubscribe(_sectionName, _query);
}

void AgentAPIIMP::Unsubscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName)
{
	m_communicator->Unsubscribe(_agent, _query, _sectionName);
	
	m_hub->Unsubscribe(_agent, _query, _sectionName);
}

void AgentAPIIMP::SendEvent(const Event& _event)
{
	m_hub->SendEvent(_event);
}

}
