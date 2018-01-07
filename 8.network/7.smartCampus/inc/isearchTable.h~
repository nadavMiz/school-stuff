#ifndef __ISEARCH_TABLE_H__
#define __ISEARCH_TABLE_H__

#include <tr1/memory>

#include "uncopyable.h"
#include "query.h"

namespace smartCampus
{

template <class T>
class ISearchTable: private Uncopyable
{

public:
	//SearchTable(); default CTOR
	virtual ~ISearchTable() = 0;
	virtual void Insert(const Query& _query, const T& _value) = 0;
	virtual void Remove(const T& _value) = 0;
	virtual void Remove(const Query& _query) = 0;
	virtual void Clear() = 0;
	virtual std::vector<T>& Find(const Query& _query) const = 0;
	virtual bool IsPresent(const Query& _query) const = 0;
};

template <class T>
inline ISearchTable<T>::~ISearchTable(){}


}

#endif /* __ISEARCH_TABLE_H__ */

