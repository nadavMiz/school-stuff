#ifndef __THREADABLE_H__
#define __THREADABLE_H__

class Threadable
{
	public:
		virtual ~Threadable() = 0;
		virtual void RunThread() = 0;

};

inline Threadable::~Threadable(){}

#endif /* __THREADABLE_H__ */

