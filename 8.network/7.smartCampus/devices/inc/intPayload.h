#ifndef __INT_PAYLOAD_H__
#define __INT_PAYLOAD_H__

#include "payload.h"

class IntPayload: public Payload
{
	public:
		IntPayload(int _data): m_data(_data) {}
		virtual ~IntPayload () {}
		
		int GetData() const { return m_data;}

	private:
		/* data */
		int m_data;
};

#endif /* __INT_PAYLOAD_H__ */



