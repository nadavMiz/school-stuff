#ifndef __TREE_REGISTRATION_TABLE_H__
#define __TREE_REGISTRATION_TABLE_H__

#include <map>

#include "registrationTable.h"

namespace smartCampus
{

class TreeRegistrationTable: public RegistrationTable
{
public:
	TreeRegistrationTable();
	virtual ~TreeRegistrationTable();
	virtual void Insert(Agent*, const Query& _query);
	virtual bool Remove(Agent*, const Query& _query);
	virtual const std::vector<Agent*>& Find(const Query& _query) const;
	virtual std::vector<Agent*>& Find(const Query& _query);
	
private:
	std::map<std::string, VectorRegistrationTable> m_table;
};

}

#endif /* __TREE_REGISTRATION_TABLE_H__ */

