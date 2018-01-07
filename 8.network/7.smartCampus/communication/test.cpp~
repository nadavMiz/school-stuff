#include <cstring> //strlen
#include <stdexcept> //runtime_error
#include <iostream>

#include "shmpProtocol.h"
#include "defaultEventFactory.h"
#include "mu_test.h"

using namespace smartCampus;

UNIT(protocol_parse_msg)

char registerMsg[] = "SHMP: register hub1 127.0.0.1 subs:2000 evts:3000";
char unregisterMsg[] = "SHMP: unregister";
char badMsg[] = "unregister hub1";

ShmpProtocol protocol;
ProtocolMsgPtr msg = protocol.ParseMessage(registerMsg, strlen(registerMsg) + 1);
ASSERT_THAT(msg->m_topic == "register");
ASSERT_THAT(msg->m_values.size() == 4);
ASSERT_THAT(msg->m_values[2] == "subs:2000");

msg = protocol.ParseMessage(unregisterMsg, strlen(unregisterMsg) + 1);
ASSERT_THAT(msg->m_topic == "unregister");
ASSERT_THAT(msg->m_values.empty());

try
{
	msg = protocol.ParseMessage(badMsg, strlen(badMsg) + 1);
	ASSERT_THAT(1);
}
catch(const std::runtime_error& _err){}

END_UNIT

/*----------------------------------------*/

UNIT(protocol_create_msg)

ShmpProtocol protocol;
ProtocolMsg msg;

msg.m_topic = "register";
msg.m_values.push_back("hub1");
msg.m_values.push_back("127.0.0.1");
msg.m_values.push_back("subs:2000");
msg.m_values.push_back("evts:3000");

std::string retMsg = protocol.CreateMsg(msg);
ASSERT_THAT(retMsg == "SHMP: register hub1 127.0.0.1 subs:2000 evts:3000");

END_UNIT

/*---------------------------------------------*/

UNIT(protocol_error_msg)

ShmpProtocol protocol;

ASSERT_THAT(protocol.GetResponse("ok") == "SHMP: status 200 OK");
ASSERT_THAT(protocol.GetResponse("bad request") == "SHMP: status 400 Bad Request");
ASSERT_THAT(protocol.GetResponse("error") == "SHMP: status 500 Internal Server Error");
try
{
	protocol.GetResponse("ok2");
	ASSERT_THAT(0);
}
catch(const std::runtime_error& _err){}

END_UNIT

/*---------------------------------------------*/

UNIT(default_event_factory)

char eventMsg[] = "SHMP: event topic:fire type:123 section:hub2 floor:5 room:6 agent:fire_alarm-6 status:on tmp:54";

ShmpProtocol protocol;

ProtocolMsgPtr msg = protocol.ParseMessage(eventMsg, strlen(eventMsg) + 1);

DefaultEventFactory factory;
Event newEvent = factory.CreateEvent(*msg);

ASSERT_THAT(newEvent->m_type == "fire");
ASSERT_THAT(newEvent->m_floor == 5);
ASSERT_THAT(newEvent->m_room == "6");
ASSERT_THAT((static_cast<const DefaultEvent*>(newEvent.GetEventImp()))->m_payload.size() == 2);

END_UNIT

/*---------------------------------------------*/

TEST_SUITE(smartCampus_communication)

TEST(protocol_parse_msg)
TEST(protocol_create_msg)
TEST(protocol_error_msg)
TEST(default_event_factory)

END_SUITE
