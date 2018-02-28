#ifndef __REGISTRAR_CONECTOR_H__
#define __REGISTRAR_CONECTOR_H__

#include <string>

#include "sectionData.h"

namespace smartCampus
{

class RegistrarConnector
{
public:
	//RegistrarConnector();
	virtual ~RegistrarConnector() = 0;

	virtual SectionData GetSectionData(const std::string& _data) = 0;
};


inline RegistrarConnector::~RegistrarConnector(){}

}
#endif /* __REGISTRAR_CONECTOR_H__ */

