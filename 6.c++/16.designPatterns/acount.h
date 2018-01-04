#ifndef __ACOUNT_H__
#define __ACOUNT_H__

#include <string>

#include "observer.h"

class AcountImp;

class Acount: public Observer
{
	public:
		Acount(const string& _type, Subject* _subject); //throw const char*
		virtual ~Acount();
		
		virtual void Update(const Subject* ChngSubject);
		
	private:
		/* data */
		AcountImp* m_acount;
};

#endif /* __ACOUNT_H__ */

