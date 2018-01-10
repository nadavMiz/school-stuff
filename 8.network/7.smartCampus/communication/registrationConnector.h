#ifndef __REGISTRATION_CONNECTOR_H__
#define __REGISTRATION_CONNECTOR_H__

#include <string>
#include <map>

#include "query.h"
#include "isearchTable.h"
#include "registrarConector.h"
#include "uncopyable.h"
#include "protocolCommSocket.h"
#include "querySerializer.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<RegistrarConnector> RegistrarConectorPtr;
typedef std::tr1::shared_ptr<ISearchTable> ISearchTablePtr;

class RegistrationConnector: private Uncopyable
{
public:
	RegistrationConnector(RegistrarConectorPtr _registrar, ProtocolPtr _protocol);
	//~RegistrationConnector();
	
	void Register(const std::string& _sectionName, const Query& _query);
	void Unregister(const std::string& _sectionName, const Query& _query);

private:
	class Record
	{
	public:
		Record(const char* _ip, int _port, ProtocolPtr _protocol);
		//~Record();
		void Register(const Query& _query);
		void Unregister(const Query& _query);
		void Empty() const;
	private:
		ISearchTablePtr m_queries;
		ProtocolCommSocket m_socket;
		
		static const QuerySerializer m_serializer;
		
	private:
		ProtocolMsg GetRequestMsg(const Query& _query, const std::string& _topic) const;
		void SendRequest(const Query& _query, const std::string& _topic);
		void ReciveResponse();
	};

private:
	/* data */
	RegistrarConectorPtr m_registrar;
	ProtocolPtr m_protocol;
	std::map<std::string, std::tr1::shared_ptr<Record> >  m_sectionRegistrations;
};

}

#endif /* __REGISTRATION_CONNECTOR_H__ */

