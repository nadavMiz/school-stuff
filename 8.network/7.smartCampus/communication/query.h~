#ifndef QUERY_H
#define QUERY_H

#include <string>

namespace smartCampus
{

struct Query
{
	Query();
	std::string m_topic;
	std::string m_room;
	std::string m_floor;
	std::string m_section;
	
	inline bool operator==(const Query& _query);
};

inline bool Query::operator==(const Query& _query)
{
	return m_topic == _query.m_topic && m_room == _query.m_room && m_floor == _query.m_floor;
}

}

#endif /* QUERY_H */

