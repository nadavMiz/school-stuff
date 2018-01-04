#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <tr1/memory>

#include "protocol.h"
#include "nthread.h"
#include "server.h"
#include "hub.h"

namespace smartCampus
{

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
		Hub* m_hub;
		bool m_isRunning;
};

}
#endif /* COMMUNICATOR_H */

