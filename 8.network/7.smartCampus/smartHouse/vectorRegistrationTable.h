#ifndef __VECTOR_REGISTRATION_TABLE_H__
#define __VECTOR_REGISTRATION_TABLE_H__

#include <vector>
#include <map>

#include "registrationTable.h"

namespace smartCampus
{

class VectorRegistrationTable
{
public:
	//VectorRegistrationTable();
	//virtual ~VectorRegistrationTable();
	virtual void Insert(Agent*, const Query& _query);
	virtual bool Remove(Agent*, const Query& _query);
	virtual std::vector<Agent*> Find(const Query& _query) const;
	virtual bool Empty() const;

private:
	static bool CompareQueryToPair(const std::pair<Query, Agent*>& _pair, const Query& _first);
	static bool CompareQueries(const Query& _first, const Query& _second);
	static bool CompareQuerieValues(const std::string& _a, const std::string& _b);
	static bool ComparePairs(const std::pair<Query, Agent*>& _pair);
	
	
	bool IsExist(Agent* _agent, const Query& _query) const;

private:
	/* data */
	std::vector<std::pair<Query, Agent*> > m_table;
};

inline bool VectorRegistrationTable::CompareQueries(const Query& _first, const Query& _second)
{
	return (_first.m_topic == _second.m_topic && CompareQuerieValues(_first.m_room, _second.m_room) && CompareQuerieValues(_first.m_floor, _second.m_floor));
}

inline bool VectorRegistrationTable::CompareQuerieValues(const std::string& _a, const std::string& _b)
{
	return (_a == "ALL" || _a == _b);
}

inline bool VectorRegistrationTable::CompareQueryToPair(const std::pair<Query, Agent*>& _pair, const Query& _query)
{
	return CompareQueries(_pair.first, _query);
}

inline bool VectorRegistrationTable::Empty() const
{
	return m_table.empty();
}


}

#endif /* __VECTOR_REGISTRATION_TABLE_H__ */

