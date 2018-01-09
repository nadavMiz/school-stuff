#include <string>
#include <sstream>

#include "dbRegistrarConnector.h"
#include "netExceptions.h" //BadRequest_error

namespace smartCampus
{

DbRegistrarConnector::DbRegistrarConnector(): m_registrar("Registrar"){}

SectionData DbRegistrarConnector::GetSectionData(const std::string& _data)
{
	std::stringstream ss;
	ss << "SELECT * FROM Sections WHERE section_name = '" << _data << "'";
	
	ResultSetPtr results = m_registrar.Query(ss.str());
	
	return CreateSectionData(results);
}

SectionData DbRegistrarConnector::CreateSectionData(ResultSetPtr _results)
{
	if(!_results->next())
	{
		throw netcpp::BadRequest_error("invalid section name");
	}
	
	SectionData data;
	
	data.m_name = _results->getString("section_name");
	data.m_ip = _results->getString("ip");
	data.m_msgPort = _results->getInt("msg_port");
	data.m_regtistrationPort = _results->getInt("registration_port");
	
	return data;
}

}
