#include "observer.h"
#include "subject.h"

Observer::Observer(Subject* _subject, const string& _type)
{
	if(0 == _subject)
	{
		throw "null subject";
	}
	_subject->Attach(this, _type);
	
	sbj = _subject;
	m_type = _type;
}

Observer::~Observer()
{
	sbj->Detach(this, m_type);
}
