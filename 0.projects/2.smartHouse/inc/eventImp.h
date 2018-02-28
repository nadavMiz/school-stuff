#ifndef __EVENT_IMP_H__
#define __EVENT_IMP_H__

#include <string>

#include "payload.h"

using namespace std;

class EventImp
{
	public:
		EventImp(const string& _type, const string& _room, unsigned int _floor);
		EventImp(EventImp& _event);
		EventImp& operator=(EventImp& _event);
		
		virtual ~EventImp();

		const string& GetType() const {return m_type;}
		const string& GetRoom() const {return m_room;}
		unsigned int GetFloor() const {return m_floor;}

	private:
		/* data */
		string m_type;
		string m_room;
		unsigned int m_floor;
};

#endif /* __PAYLOAD_H__ */
