#ifndef IHANDLER_H
#define IHANDLER_H

#include <tr1/memory>

#include "serverEnums.h"
#include "socket.h"

namespace netcpp
{

typedef std::tr1::shared_ptr<Socket> SocketPtr;

class IHandler
{
public:
	virtual ~IHandler() = 0;
	virtual EventStatus HandleError(SocketPtr _socket){ return e_statusToDelete;}
	virtual EventStatus HandleEvent(SocketPtr _socket){ return e_statusOk;}
	
};

inline IHandler::~IHandler(){}

}
#endif /* IHANDLER_H */

