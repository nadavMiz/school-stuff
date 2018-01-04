#ifndef __SUBJECT_H__
#define __SUBJECT_H__

#include <map>
#include <string>

using namespace std;

class Observer;

class Subject
{
	public:
	virtual ~Subject() {}

    virtual void Attach(Observer* _obs, const string& _type);
    virtual void Detach(Observer* _obs, const string& _type);

protected:
	Subject() {}
	virtual void Notify(const string& _type) const;
	
	multimap<string, Observer*> m_observers;
};

#endif /* __SUBJECT_H__ */

