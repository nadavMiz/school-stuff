#ifndef __REGISTRATION_CONNECTOR_H__
#define __REGISTRATION_CONNECTOR_H__

#include <string>
#include <map>

#include "nlog.h"
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
private:
	class Record
	{
	public:
		Record(const char* _ip, int _port, ProtocolPtr _protocol);
		//~Record();
		void Register(const Query& _query);
		void Unregister(const Query& _query);
		inline bool Empty() const;
	private:
		ISearchTablePtr m_queries;
		ProtocolCommSocket m_socket;
		Nlog* m_log;
		
		static const QuerySerializer m_serializer;
		
	private:
		void InitializeRequestMsg(const Query& _query, const std::string& _topic, ProtocolMsg& _msg) const;
		void SendRequest(const Query& _query, const std::string& _topic);
		void ReciveResponse();
	};
typedef std::tr1::shared_ptr<RegistrationConnector::Record> RecordPtr;

public:
	RegistrationConnector(RegistrarConectorPtr _registrar, ProtocolPtr _protocol);
	//~RegistrationConnector();
	
	void Register(const std::string& _sectionName, const Query& _query);
	void Unregister(const std::string& _sectionName, const Query& _query);

private:
	/* data */
	RegistrarConectorPtr m_registrar;
	ProtocolPtr m_protocol;
	std::map<std::string, RecordPtr >  m_sectionRegistrations;
	Nlog* m_log;
	
private:
	RecordPtr GetRecord(const std::string& _section);
	RecordPtr CreateRecord(const std::string& _section) const;
};


/*------------------------RegistrationConnector::Record-----------------------------------*/

inline bool RegistrationConnector::Record::Empty() const
{
	return m_queries->IsEmpty();
}

}

#endif /* __REGISTRATION_CONNECTOR_H__ */

