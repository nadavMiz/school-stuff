#ifndef NETWORK_AGENT_H
#define NETWORK_AGENT_H

#include <map>
#include <set>
#include <tr1/memory>

#include "agent.h"
#include "protocolCommSocket.h"
#include "agentData.h"
#include "isearchTable.h"
#include "eventSerializer.h"
#include "query.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<ProtocolCommSocket> ClientSocketPtr;
typedef std::tr1::shared_ptr<ISearchTable> ISearchTablePtr;

class NetworkAgent: public Agent
{
public:
	NetworkAgent(ClientSocketPtr _socket, Hub* _hub);
	virtual ~NetworkAgent();
	
	virtual bool IsRelevantEvent(const Event& _event) const;
	virtual void ReciveEvent(const Event& _event);
	
	void AddRegistration(const Query& _query);
	void RemoveRegistration(const Query& _query);

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
	ISearchTablePtr m_topics;
	EventSerializer m_serializer;
	
	static const AgentData& GetAgentData();
	Query ParseEvent(const Event& _event) const;
};

inline const AgentData& NetworkAgent::NetworkAgentData::GetData() const
{
	return m_agentData;
}

inline void NetworkAgent::AddRegistration(const Query& _query)
{
	m_topics->Insert(_query);
}

inline void NetworkAgent::RemoveRegistration(const Query& _query)
{
	m_topics->Remove(_query);
}

}
#endif /* NETWORK_AGENT_H */

