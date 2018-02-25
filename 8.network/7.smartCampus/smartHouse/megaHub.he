#ifndef __MEGA_HUB_H__
#define __MEGA_HUB_H__

#include <tr1/memory>
#include <map>
#include <string>

#include "hub.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<Hub> HubPtr;

class MegaHub: public Hub
{
public:
	MegaHub();
	virtual ~MegaHub();
	virtual bool Subscribe(Agent* _agent);
	virtual bool Unsubscribe(Agent* _agent);
	virtual void Subscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName);
	virtual void Unsubscribe(Agent* _agent, const smartCampus::Query& _query, const std::string& _sectionName);
	virtual void SendEvent(const Event _event) = 0;

private:
	/* data */
	std::map<std::string, HubPtr> m_hubs;
};

}

#endif /* __MEGA_HUB_H__ */

