#include "string.h"

#include "player.h"

player_t::player_t(const char* _name, unsigned int _cardCapacity): m_hand(_cardCapacity)
{
	m_name = new char[strlen(_name)];
	if(0 == m_name)
	{
		//TODO something
	}
	strcpy(m_name, _name);
}
