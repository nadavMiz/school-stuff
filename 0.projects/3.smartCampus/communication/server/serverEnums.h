#ifndef __SERVER_ENUMS_H__
#define __SERVER_ENUMS_H__

namespace netcpp
{

enum EventType
{
	e_typeNull = 0,
	e_typeRead,
	e_typeWrite,
	e_typeError
};

enum EventStatus
{
	e_statusOk = 0,
	e_statusError,
	e_statusToDelete
};

}

#endif /* __SERVER_ENUMS_H__ */

