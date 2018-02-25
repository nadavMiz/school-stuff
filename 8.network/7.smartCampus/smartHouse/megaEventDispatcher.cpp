#include "megaEventDispatcher.h"
#include "singleSectionDispatcher.h"

namespace smartCampus
{

MegaEventDispatcher::MegaEventDispatcher()
:	m_mainDispatcher(new SingleSectionDispatcher)
{}

void MegaEventDispatcher::Subscribe(Agent* _agent, const smartCampus::Query& _query)
{
	m_mainDispatcher->Subscribe(_agent, _query);
}

EventDispatcherPtr MegaEventDispatcher::AddDispatcher(const std::string& _section)
{
	EventDispatcherPtr newDispatcher(new SingleSectionDispatcher);
	
	m_dispatchers.insert(std::pair<std::string, EventDispatcherPtr>(_section, newDispatcher));
	
	return newDispatcher;
}

void MegaEventDispatcher::Subscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _section)
{
	EventDispatcherPtr dispatcher;

	std::map<std::string, EventDispatcherPtr>::iterator dispatcherItr = m_dispatchers.find(_section);
	if(m_dispatchers.end() == dispatcherItr)
	{
		dispatcher = AddDispatcher(_section);
	}
	else
	{
		dispatcher = dispatcherItr->second;
	}
	
	dispatcher->Subscribe(_agent, _query);
}

bool MegaEventDispatcher::Unsubscribe(Agent* _agent)
{
	return m_mainDispatcher->Unsubscribe(_agent);
}

bool MegaEventDispatcher::Unsubscribe(Agent* _agent, const std::string& _section)
{
	std::map<std::string, EventDispatcherPtr>::iterator dispatcherItr = m_dispatchers.find(_section);
	if(m_dispatchers.end() == dispatcherItr)
	{
		return false;
	}
	
	return dispatcherItr->second->Unsubscribe(_agent);
}

void MegaEventDispatcher::SendEvent(const Event _event)
{
	m_mainDispatcher->SendEvent(_event);
}

}
