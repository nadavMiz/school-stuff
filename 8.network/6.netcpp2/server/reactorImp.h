#ifndef REACTOR_IMP_H
#define REACTOR_IMP_H

#include <set>

#include "ireactor.h"
#include "socket.h"
#include "selectSet.h"

namespace netcpp
{

class ReactorImp: public IReactor
{
public:
	ReactorImp(unsigned int _maxSockets);
	virtual ~ReactorImp(){}
	virtual void AddSocket(SocketPtr _socket, IHandlerPtr _handler);
	virtual void RemoveSocket(SocketPtr _socket);
	virtual void Run();
	
	//inline void SetDispatcher(std::tr1::shared_ptr<IDispatcher> _dispatcher);

protected:
	 //IDispatcherPtr m_dispatcher;


private:
	std::set<SocketPtr> m_sockets;
	SelectSet m_selectSet;
	unsigned int m_maxSockets;

private:
	void HandleSingleEvent(SocketPtr _socket, unsigned int& _NumActiveSockets);
	
};

}
#endif /* REACTOR_IMP_H */

