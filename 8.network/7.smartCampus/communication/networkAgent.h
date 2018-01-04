#ifndef NETWORK_AGENT_H
#define NETWORK_AGENT_H

#include <map>
#include <set>
#include <tr1/memory>

#include "agent.h"
#include "clientSocket.h"
#include "agentData.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<netcpp::ClientSocket> ClientSocketPtr;

class NetworkAgent: public Agent
{
public:
	NetworkAgent(ClientSocketPtr _socket, Hub* _hub);
	virtual ~NetworkAgent();
	
	virtual bool IsRelevantEvent(const Event& _event) const;
	virtual void ReciveEvent(const Event& _event);
	
	void AddRegistration(const std::string& _topic, const std::string& _room);
	void RemoveRegistration(const std::string& _topic, const std::string& _room);

public:
	class NetworkAgentData
	{
	public:
		NetworkAgentData();
		inline const AgentData& GetData() const;
	private:
		AgentData m_agentData;
	};

private:
	/* data */
	ClientSocketPtr m_socket;
	std::multimap<std::string, std::multiset<std::string> > m_topics;
	
	static const NetworkAgentData m_networkAgentData;
};

inline const AgentData& NetworkAgent::NetworkAgentData::GetData() const
{
	return m_agentData;
}

}
#endif /* NETWORK_AGENT_H */

