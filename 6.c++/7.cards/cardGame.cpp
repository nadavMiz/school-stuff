#include "cardGame.h"

cardGame_t::cardGame_t(unsigned int _playerCapacity, unsigned int _boardCapacity): m_board(_boardCapacity)
{
	m_playerCapacity = _playerCapacity;
}

bool cardGame_t::AddPlayer(const player_t* _player)
{
	if(m_players.size() == m_playerCapacity)
	{
		return false;
	}
	
	m_players.push_back((player_t*)_player);
	return true;
}

player_t* cardGame_t::RemovePlayer(const player_t* _player)
{
	for(unsigned int i = 0; i < m_players.size(); i++)
	{
		if(_player == m_players[i])
		{
			player_t* player = m_players[i];
			m_players.erase(m_players.begin() + i);
			return player;
		}
	}
	
	return 0;
}

player_t* cardGame_t::RemovePlayer(unsigned int _index)
{
	if(_index >= m_players.size())
	{
		return 0;
	}
	
	player_t* player = m_players[_index];
	m_players.erase(m_players.begin() + _index);
	return player;
}

