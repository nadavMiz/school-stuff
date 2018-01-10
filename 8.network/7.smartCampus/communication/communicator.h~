#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <tr1/memory>

#include "protocol.h"
#include "nthread.h"
#include "server.h"
#include "hub.h"
#include "registrarConector.h"


namespace smartCampus
{

typedef std::tr1::shared_ptr<RegistrarConnector> RegistrarConectorPtr;

class Communicator
{
public:
	Communicator(Hub* _hub);
	~Communicator();

private:
	/* data */
	std::tr1::shared_ptr<Protocol> m_protocol;
	std::tr1::shared_ptr<netcpp::Server> m_server;
	advcpp::sync::Nthread<netcpp::Server> m_serverThread;
	RegistrarConectorPtr m_registrarConnector; 
	
private:
	void AddRegistrationHandler(Hub* _hub);
	void AddEventHandler(Hub* _hub);
};

}
#endif /* COMMUNICATOR_H */

