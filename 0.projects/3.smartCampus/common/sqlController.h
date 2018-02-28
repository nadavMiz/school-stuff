#ifndef SQLCONTROLLER_H
#define SQLCONTROLLER_H

#include "mysql_connection.h"

#include <tr1/memory>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

typedef std::tr1::shared_ptr<sql::ResultSet> ResultSetPtr;

namespace netcpp
{

class SqlController
{
public:
	SqlController(const std::string& _tableName);
	// ~SqlController(); default DTOR
	ResultSetPtr Query(const std::string& _statement) const;
	void InsertToTable(const std::string& _tableName , const char* _str, ...);
	

private:
	/* data */
	std::tr1::shared_ptr<sql::Connection> m_con;
};

}
#endif /* SQLCONTROLLER_H */

