#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include <tr1/memory>

#include "uncopyable.h"
#include "nthread.h"
#include "query.h"
#include "sqlController.h"
#include "sectionData.h"
#include "inCommunication.h"

class Hub;

namespace smartCampus
{

class Protocol;
class RegistrarConnector;
class RegistrationConnector;

typedef std::tr1::shared_ptr<RegistrarConnector> RegistrarConectorPtr;
typedef std::tr1::shared_ptr<RegistrationConnector> RegistrationConectorPtr;
typedef std::tr1::shared_ptr<netcpp::SqlController> SqlControllerPtr;

class Communicator: private Uncopyable
{
public:
	Communicator(Hub* _hub, SqlControllerPtr _dataBase);
	//~Communicator();
	
	void Subscribe(const std::string& _sectionName, const Query& _query);
	void Unsubscribe(const std::string& _sectionName, const Query& _query);

private:
	/* data */
	std::tr1::shared_ptr<Protocol> m_protocol;
	RegistrarConectorPtr m_registrarConnector;
	RegistrationConectorPtr m_registrationConnector;
	InCommunication m_inCommunication;
	
private:
	SectionData GetSectionData(SqlControllerPtr _dataBase) const;
	SectionData CreateSectionData(ResultSetPtr _results) const;
	void AddRegistrationHandler(Hub* _hub, int _port);
	void AddEventHandler(Hub* _hub, int _port);
};

}
#endif /* COMMUNICATOR_H */

