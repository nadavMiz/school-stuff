#ifndef __SMART_BUILDING_INFORMATION_H__
#define __SMART_BUILDING_INFORMATION_H__

#include "uncopyable.h"
#include "sectionData.h"

namespace smartCampus
{

class ISmartBuildingInformation: private Uncopyable
{
public:
	//ISmartBuildingInformation();
	virtual ~ISmartBuildingInformation () = 0;
	
	virtual SectionData GetSectionData(const std::string& _data) = 0;
};

inline ISmartBuildingInformation::~ISmartBuildingInformation(){}

}
#endif /* __SMART_BUILDING_INFORMATION_H__ */

