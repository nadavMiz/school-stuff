#ifndef __IN_COMMUNICATION_H_H__
#define __IN_COMMUNICATION_H_H__

#include <tr1/memory>

#include "uncopyable.h"
#include "nthread.h"
#include "sqlController.h"
#include "sectionData.h"

namespace netcpp
{
	class Server;
}

class Hub;

namespace smartCampus
{

class Protocol;
class RegistrationHandler;
class RegistrarConnector;

typedef std::tr1::shared_ptr<Protocol> ProtocolPtr;
typedef std::tr1::shared_ptr<netcpp::SqlController> SqlControllerPtr;
typedef std::tr1::shared_ptr<RegistrationHandler> RegistrationHandlerPtr;
typedef std::tr1::shared_ptr<RegistrarConnector> RegistrarConectorPtr;

class InCommunication: private Uncopyable
{
public:
	InCommunication(Hub* _hub, ProtocolPtr _protocol, RegistrarConectorPtr _registrar, SqlControllerPtr _dataBase);
	~InCommunication();

private:
	/* data */
	std::tr1::shared_ptr<Protocol> m_protocol;
	std::tr1::shared_ptr<netcpp::Server> m_server;
	advcpp::sync::Nthread<netcpp::Server> m_serverThread;
	
private:
	SectionData GetSectionData(SqlControllerPtr _dataBase) const;
	SectionData CreateSectionData(ResultSetPtr _results) const;
	void AddRegistrationHandler(Hub* _hub, int _port, RegistrarConectorPtr _registrar);
	void AddEventHandler(Hub* _hub, int _port);
};

}

#endif /* __IN_COMMUNICATION_H_H__ */

