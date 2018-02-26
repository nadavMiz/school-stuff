#include <iostream>
#include <vector>

#include "agent.h"
#include "query.h"
#include "vectorRegistrationTable.h"

using namespace smartCampus;

int main()
{
	Agent* a = (Agent*)2;
	Agent* b = (Agent*)0;
	Query q1, q2;
	q1.m_topic = "fire";
	q1.m_room = "fire";
	q2.m_topic = "fire";
	
	
	VectorRegistrationTable regist;
	
	regist.Insert(a,q1);
	regist.Insert(b,q2);
	
	std::vector<Agent*> vec = regist.Find(q2);
	
	std::cout << vec.size() << std::endl;
	
	return 0;
}
