#ifndef __REGISTRATION_TABLE_H__
#define __REGISTRATION_TABLE_H__

#include <vector>

#include "agent.h"
#include "query.h"

namespace smartCampus
{

class RegistrationTable
{
public:
	//RegistrationTable();
	virtual ~RegistrationTable() = 0;
	virtual void Insert(Agent*, const Query& _query) = 0;
	virtual bool Remove(Agent*, const Query& _query) = 0;
	virtual const std::vector<Agent*> Find(const Query& _query) const = 0;
	virtual std::vector<Agent*>& Find(const Query& _query) = 0;
	virtual bool Empty() const = 0;
};

}

#endif /* __REGISTRATION_TABLE_H__ */

