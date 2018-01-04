#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <tr1/memory>

#include "protocolMsg.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<ProtocolMsg> ProtocolMsgPtr;

class Protocol
{
public:
	//Protocol(); default CTOR
	virtual ~Protocol() = 0;
	virtual ProtocolMsgPtr ParseMessage(char* _data, std::size_t _length) = 0;
	virtual std::string CreateMsg(const ProtocolMsg& _msg) = 0;
	virtual std::string GetResponse(const std::string& _type) = 0;

};

inline Protocol::~Protocol(){}

}
#endif /* __PROTOCOL_H__ */

