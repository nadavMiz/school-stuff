#ifndef __HUB_H__
#define __HUB_H__

class Agent;
class Event;

class Hub
{
	public:
		Hub() {}
		virtual ~Hub() {}
		virtual bool Subscribe(Agent* _agent) = 0;
		virtual bool Unsubscribe(Agent* _agent) = 0;
		virtual void SendEvent(const Event _event) = 0;

	private:
		/* data */
};

#endif /* __MY_HUB_H__ */

