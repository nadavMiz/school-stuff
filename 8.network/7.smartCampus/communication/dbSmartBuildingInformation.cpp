#include <stdexcept>

#include "dbSmartBuildingInformation.h"

namespace smartCampus
{

DBSmartBuildingInformation::DBSmartBuildingInformation(): 
	m_log(NlogFactory::GetLog1("system.log")){}

SectionData DBSmartBuildingInformation::CreateSectionData(ResultSetPtr _results)
{
	if(!_results->next())
	{
		m_log->write("invalid section name", "DBSmartBuildingInformation::CreateSectionData");
		throw std::runtime_error("invalid section name");
	}
	
	SectionData data;
	
	data.m_name = _results->getString("section_name");
	data.m_ip = _results->getString("ip");
	data.m_msgPort = _results->getInt("msg_port");
	data.m_regtistrationPort = _results->getInt("registration_port");
	
	return data;
}

ResultSetPtr DBSmartBuildingInformation::GetInformationResultSet(const netcpp::SqlController& _dataBase)
{
	return _dataBase.Query("SELECT * FROM Info");
}

SectionData DBSmartBuildingInformation::GetSectionData(const std::string& _configPath)
{
	netcpp::SqlController dataBase(_configPath);
	
	ResultSetPtr resultSet = GetInformationResultSet(dataBase);
	
	return CreateSectionData(resultSet);
}

}
