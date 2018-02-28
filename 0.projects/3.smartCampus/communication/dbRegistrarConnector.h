#ifndef __DB_REGISTRAR_CONNECTOR_H__
#define __DB_REGISTRAR_CONNECTOR_H__

#include "registrarConector.h"
#include "sqlController.h"
#include "nlog.h"

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
	Nlog* m_log;
};

}
#endif /* __DB_REGISTRAR_CONNECTOR_H__ */

