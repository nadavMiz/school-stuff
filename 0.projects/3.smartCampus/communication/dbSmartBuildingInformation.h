#ifndef __DB_SMART_BUILDING_INFORMATION_H__
#define __DB_SMART_BUILDING_INFORMATION_H__

#include "iSmartBuildingInformation.h"
#include "nlogFactory.h"
#include "sqlController.h"

namespace smartCampus
{

class DBSmartBuildingInformation: public ISmartBuildingInformation
{
public:
	DBSmartBuildingInformation();
	//virtual ~DBSmartBuildingInformation();
	
	virtual SectionData GetSectionData(const std::string& _configPath);
	
private:
	SectionData CreateSectionData(ResultSetPtr _results);
	ResultSetPtr GetInformationResultSet(const netcpp::SqlController& _dataBase);
	
	Nlog* m_log;
};

}

#endif /* __DB_SMART_BUILDING_INFORMATION_H__ */

