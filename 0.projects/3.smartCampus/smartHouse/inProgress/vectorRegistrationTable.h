#ifndef __VECTOR_REGISTRATION_TABLE_H__
#define __VECTOR_REGISTRATION_TABLE_H__

#include <vector>
#include <map>

#include "registrationTable.h"

namespace smartCampus
{

class VectorRegistrationTable: public RegistrationTable
{
public:
	//VectorRegistrationTable();
	//virtual ~VectorRegistrationTable();
	virtual void Insert(Agent*, const Query& _query);
	virtual bool Remove(Agent* _agent); // no throw. return false on failure
	virtual bool Remove(Agent*, const Query& _query); // no throw. return false on failure
	virtual std::vector<Agent*> Find(const Event& _event) const;
	virtual bool Empty() const;

private:
	static bool CompareAgentToPair(const std::pair<Query, Agent*>& _pair, const Agent* _agent);
	static bool CompareEventToPair(const std::pair<Query, Agent*>& _pair, const Event& _event);
	static bool CompareQuerieValues(const std::string& _a, const std::string& _b);
	static bool CompareQuerieValues(const std::string& _a, unsigned int _b);
	
	
	bool IsExist(Agent* _agent, const Query& _query) const;

private:
	/* data */
	std::vector<std::pair<Query, Agent*> > m_table;
};

inline bool VectorRegistrationTable::CompareQuerieValues(const std::string& _a, const std::string& _b)
{
	return (_a == "ALL" || _a == _b);
}

inline bool VectorRegistrationTable::CompareQuerieValues(const std::string& _a, unsigned int _b)
{
	return (_a == "ALL" || (unsigned int)std::stoi(_a) == _b);
}

inline bool VectorRegistrationTable::Empty() const
{
	return m_table.empty();
}


}

#endif /* __VECTOR_REGISTRATION_TABLE_H__ */

