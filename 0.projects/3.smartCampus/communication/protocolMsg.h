#ifndef __PROTOC_MSG_H__
#define __PROTOC_MSG_H__

#include <string>
#include <vector>
#include <iostream>
#include <algorithm> //std::copy
#include <iterator> // std::ostream_iterator

namespace smartCampus
{

struct ProtocolMsg
{
	std::string m_topic;
	std::vector<std::string> m_values;
};

std::ostream& operator<<(std::ostream& _os, const ProtocolMsg& _msg);

inline std::ostream& operator<<(std::ostream& _os, const ProtocolMsg& _msg)
{
	_os << "ProtocolMsg: topic: " << _msg.m_topic << "values: ";
	std::copy(_msg.m_values.begin(), _msg.m_values.end(), std::ostream_iterator<std::string>(_os));
	
	return _os;
}

}
#endif /* __PROTOC_MSG_H__ */

