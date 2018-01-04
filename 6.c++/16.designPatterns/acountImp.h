#ifndef __ACOUNT_IMP_H__
#define __ACOUNT_IMP_H__

#include <string>

class Subject;

class AcountImp
{
	public:
		AcountImp() {}
		virtual ~AcountImp() {}
		
		virtual void Update(const Subject* ChngSubject) = 0;
};

#endif /* __ACOUNT_IMP_H__ */

