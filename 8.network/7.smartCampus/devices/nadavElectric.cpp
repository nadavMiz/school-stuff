#include "hvac.h"
#include "sprinkler.h"
#include "fireSensor.h"
#include "signalFireSensor.h"
#include "interhubSprinkler.h"

extern "C" Agent* CreateAgent(const string& _deviceName, const AgentData& _data, Hub* _hub)
{
	if("HVAC" == _deviceName)
	{
		return new Hvac(_data, _hub);
	}
	else if("sprinkler" == _deviceName)
	{
		return new Sprinkler(_data, _hub);
	}
	else if("fireSensor" == _deviceName)
	{
		return new FireSensor(_data, _hub);
	}
	else if("signalFireSensor" == _deviceName)
	{
		return new SignalFireSensor(_data, _hub);
	}
	else if("interhubSprinkler" == _deviceName)
	{
		return new InterHubSprinkler(_data, _hub);
	}
	return 0;
}



