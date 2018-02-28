#include "hubImp.h"
#include "megaEventDispatcher.h"
#include "communicator.h"
#include "event.h"

namespace smartCampus
{
	
HubImp::HubImp(const std::string& _sectionName):
	m_dispatcher(new MegaEventDispatcher)
,	m_sectionName(_sectionName)	
{}
	
void HubImp::Subscribe(Agent* _agent, const smartCampus::Query& _query)
{
	m_dispatcher->Subscribe(_agent, _query);
}

void HubImp::Subscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName)
{
	m_dispatcher->Subscribe(_agent, _query, _sectionName);
	
	try
	{
		m_communicator->Subscribe(_sectionName, _query);
	}
	catch(const std::exception& _err)
	{
		m_dispatcher->Unsubscribe(_agent, _sectionName);
		throw;
	}
}

bool HubImp::Unsubscribe(Agent* _agent)
{
	return m_dispatcher->Unsubscribe(_agent);
}

bool HubImp::Unsubscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName)
{
	//TODO check if subscribed first. current function might unsbscribe someone else. also check if someone else is subscribed to the same thing
	try
	{
		m_communicator->Unsubscribe(_sectionName, _query);
	}
	catch(const std::exception& _err)
	{
		return false;
	}
	
	return m_dispatcher->Unsubscribe(_agent, _sectionName);
}

void HubImp::SendEvent(Event _event)
{
	//TODO better header filler
	_event->m_section = m_sectionName;
	
	m_dispatcher->SendEvent(_event);
}
	
void HubImp::SendEvent(Event _event, const std::string& _sectionName)
{	
	m_dispatcher->SendEvent(_event, _sectionName);
}
	
}
