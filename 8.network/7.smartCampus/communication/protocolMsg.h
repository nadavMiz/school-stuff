#ifndef __PROTOC_MSG_H__
#define __PROTOC_MSG_H__

#include <string>
#include <vector>

namespace smartCampus
{

struct ProtocolMsg
{
	std::string m_topic;
	std::vector<std::string> m_values;
};

}
#endif /* __PROTOC_MSG_H__ */

