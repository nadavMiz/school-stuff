#include <cppconn/driver.h>
#include <cstdio> // sprintf

#include "sqlController.h"



namespace netcpp
{

SqlController::SqlController(const std::string& _tableName)
{
	sql::Driver* driver = get_driver_instance();
  	m_con = std::tr1::shared_ptr<sql::Connection>(driver->connect("tcp://127.0.0.1:3306", "root", "student"));
  	m_con->setSchema(_tableName);
}

ResultSetPtr SqlController::Query(const std::string& _statement) const
{
	std::tr1::shared_ptr<sql::Statement> stmt(m_con->createStatement());
	return ResultSetPtr(stmt->executeQuery(_statement));
}

}
