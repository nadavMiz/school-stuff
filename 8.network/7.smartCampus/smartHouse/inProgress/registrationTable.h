#ifndef __REGISTRATION_TABLE_H__
#define __REGISTRATION_TABLE_H__

#include <vector>

#include "agent.h"
#include "query.h"
#include "event.h"
#include "uncopyable.h"

namespace smartCampus
{

class RegistrationTable: private Uncopyable
{
public:
	//RegistrationTable();
	virtual ~RegistrationTable() = 0;
	virtual void Insert(Agent* _agent, const Query& _query) = 0;
	virtual bool Remove(Agent* _agent);
	virtual bool Remove(Agent* _agent, const Query& _query) = 0;
	virtual std::vector<Agent*> Find(const Event& _event) const = 0;
	virtual bool Empty() const = 0;
};

inline RegistrationTable::~RegistrationTable(){}

}

#endif /* __REGISTRATION_TABLE_H__ */

