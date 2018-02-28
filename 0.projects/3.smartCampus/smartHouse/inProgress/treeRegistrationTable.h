#ifndef __TREE_REGISTRATION_TABLE_H__
#define __TREE_REGISTRATION_TABLE_H__

#include <map>
#include <tr1/memory>

#include "registrationTable.h"

namespace smartCampus
{

typedef std::tr1::shared_ptr<RegistrationTable> RegistrationTablePtr;

class TreeRegistrationTable: public RegistrationTable //uncopyable
{
public:
	//TreeRegistrationTable();
	//virtual ~TreeRegistrationTable();
	virtual void Insert(const Agent* _agent, const Query& _query);
	virtual bool Remove(const Agent* _agent); 					   // currently not implemented
	virtual bool Remove(const Agent* _agent, const Query& _query); // no throw. return false on failure
	virtual std::vector<Agent*> Find(const Event& _query) const;
	virtual bool Empty() const;
	
private:
	RegistrationTablePtr AddRegistrationTable(const std::string& _topic);
	
private:
	std::map<std::string, RegistrationTablePtr> m_table;
};

inline bool TreeRegistrationTable::Empty() const
{
	return m_table.empty();
}


}

#endif /* __TREE_REGISTRATION_TABLE_H__ */

