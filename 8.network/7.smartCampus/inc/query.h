#ifndef QUERY_H
#define QUERY_H

#include <string>

struct Query
{
	std::string m_topic;
	std::string m_room;
	std::string m_building;
	int m_floor;
};


#endif /* QUERY_H */

