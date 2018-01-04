#ifndef SMART_CLIENT_H
#define SMART_CLIENT_H

#include <list>
#include <cstddef> /* std::size_t */
#include <tr1/memory> /* tr1::shared_ptr */

#include "clientSocket.h"

namespace netcpp
{

typedef std::tr1::shared_ptr<ClientSocket> ClientPtr;
typedef void(*ClientFunction)(ClientPtr _client); 

class SmartClient
{
	public:
		SmartClient(const char* _ip, int _port, ClientFunction _func, int _probability, std::size_t _numClients);
		//~SmartClient(); default DTOR
		
		void SmartClientRoutine(std::size_t _numIterations);

	private:
		void RunAllClients();
		void RunSingleClient(std::list<ClientPtr>::iterator _clientItr);
		void CreateClients(std::size_t _numClients);

	private:
		/* data */
		std::list<ClientPtr> m_clients;
		ClientFunction m_RunFunc;
		int m_probability;
		const char* m_destIp;
		int m_destPort;
		std::size_t m_numclients;
};

}
#endif /* SMART_CLIENT_H */

