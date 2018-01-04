#ifndef __INT_EVENT_H__
#define __INT_EVENT_H__

#include "eventImp.h"

class IntEvent: public EventImp
{
	public:
		IntEvent(const string& _type, const string& _room, unsigned int _floor, int _data):
				EventImp(_type, _room, _floor) ,m_data(_data){}
		virtual ~IntEvent(){}

		int GetData() {return m_data;}

	private:
		/* data */
		int m_data;
};

#endif /* __INT_EVENT_H__ */

