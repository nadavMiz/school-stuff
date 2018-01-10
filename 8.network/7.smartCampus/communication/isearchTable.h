#ifndef __ISEARCH_TABLE_H__
#define __ISEARCH_TABLE_H__

#include <tr1/memory>

#include "uncopyable.h"
#include "query.h"

namespace smartCampus
{

class ISearchTable: private Uncopyable
{

public:
	//SearchTable(); default CTOR
	virtual ~ISearchTable() = 0;
	virtual void Insert(const Query& _query) = 0;
	virtual std::size_t Remove(const Query& _query) = 0;
	virtual bool ExactRemove(const Query& _query) = 0;
	virtual void Clear() = 0;
	virtual bool IsPresent(const Query& _query) const = 0;
	virtual bool IsEmpty() const = 0;
};

inline ISearchTable::~ISearchTable(){}


}

#endif /* __ISEARCH_TABLE_H__ */

