#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <string>

using namespace std;

class Subject;

class Observer
{
	public:

		virtual	~Observer();
		virtual void Update(const Subject* ChngSubject) = 0;
		
	protected:
		Observer(Subject* _subject, const string& _type);
		Subject* sbj;
		
	private:
		string m_type;
};

#endif /* __OBSERVER_H__ */

