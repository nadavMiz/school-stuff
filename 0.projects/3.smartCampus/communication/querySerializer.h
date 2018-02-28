#ifndef __QUERY_SERIALIZER_H__
#define __QUERY_SERIALIZER_H__

#include <string>

namespace smartCampus
{

class Query;
class ProtocolMsg;

class QuerySerializer
{
public:
	//QuerySerializer();
	//~QuerySerializer();
	void Serialize(const Query& _query, ProtocolMsg& _msg) const;
	Query Deserialize(const ProtocolMsg& _msg) const;

private:
	/* data */
	void InsertPair(const std::string& _key, const std::string& _value, ProtocolMsg& _msg) const;
};
	

}

#endif /* __QUERY_SERIALIZER_H__ */

