#include <iostream>
#include <vector>

#include "agent.h"
#include "query.h"
#include "vectorRegistrationTable.h"
#include "event.h"

using namespace smartCampus;

int main()
{
	Agent* a = (Agent*)2;
	Agent* b = (Agent*)0;
	Query q1, q2;
	q1.m_topic = "fire";
	q2.m_topic = "water";
	
	
	TreeRegistrationTable regist;
	
	regist.Insert(a,q1);
	regist.Insert(a,q2);
	Event event(new EventImp);
	event->m_topic = "reek";
	std::vector<Agent*> vec = regist.Find(event);
	
	std::cout << vec.size() << std::endl;
	
	return 0;
}
