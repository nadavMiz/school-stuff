#ifndef QUERY_H
#define QUERY_H

#include <string>
#include <iostream>

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

std::ostream& operator<<(std::ostream& _os, const Query& _query);

inline bool Query::operator==(const Query& _query)
{
	return m_topic == _query.m_topic && m_room == _query.m_room && m_floor == _query.m_floor;
}

inline std::ostream& operator<<(std::ostream& _os, const Query& _query)
{
	_os << "topic: " << _query.m_topic << "room: " << _query.m_room << "floor" << _query.m_floor << "section: " << _query.m_section;
	
	return _os;
}

}

#endif /* QUERY_H */

