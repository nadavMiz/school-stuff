#include "hubAPIImp.h"
#include "hub.h"
#include "communicator.h"

namespace smartCampus
{

HubAPIIMP::HubAPIIMP(Hub* _hub, Communicator* _communicator):
	m_hub(_hub)
,	m_communicator(_communicator)
{}

void HubAPIIMP::Subscribe(Agent* _agent, const smartCampus::Query& _query)
{
	m_hub->Subscribe(_agent);
}

void HubAPIIMP::Subscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName)
{
	m_hub->Subscribe(_agent);
	
	try
	{
		m_communicator->Subscribe(_sectionName, _query);
	}
	catch(const std::exception& _err)
	{
		m_hub->Unsubscribe(_agent);
		throw;
	}
}

void HubAPIIMP::Unsubscribe(Agent* _agent, const smartCampus::Query& _query)
{
	m_hub->Unsubscribe(_agent);
}

void HubAPIIMP::Unsubscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName)
{
	m_communicator->Unsubscribe(_sectionName, _query);
	
	m_hub->Unsubscribe(_agent);
}

void HubAPIIMP::SendEvent(const Event& _event)
{
	m_hub->SendEvent(_event);
}

}
