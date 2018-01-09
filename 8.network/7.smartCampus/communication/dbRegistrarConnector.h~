#ifndef __DB_REGISTRAR_CONNECTOR_H__
#define __DB_REGISTRAR_CONNECTOR_H__

#include "registrarConector.h"
#include "sqlController.h"

namespace smartCampus
{

class DbRegistrarConnector: public RegistrarConnector
{
public:
	DbRegistrarConnector();
	//virtual ~DbRegistrarConnector();
	
	virtual SectionData GetSectionData(const std::string& _data);

private:
	/* data */
	netcpp::SqlController m_registrar;
	
private:
	SectionData CreateSectionData(ResultSetPtr _results);
};

}
#endif /* __DB_REGISTRAR_CONNECTOR_H__ */

