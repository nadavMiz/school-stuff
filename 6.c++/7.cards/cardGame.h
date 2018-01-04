#ifndef __CardGame_H__
#define __CardGame_H__

#include <vector>

#include "player.h"
#include "deck.h"
#include "hand.h"

class cardGame_t
{
	public:
		cardGame_t(unsigned int _playerCapacity, unsigned int _boardCapacity);
		virtual ~cardGame_t(){};
		virtual void Play() = 0;
		
		bool AddPlayer(const player_t* _player);
		player_t* RemovePlayer(const player_t* _player);
		player_t* RemovePlayer(unsigned int _index);

	protected:
		/* data */
		std::vector<player_t*> m_players;
		hand_t m_board;
		deck_t* m_deck;
		unsigned int m_playerCapacity;
};

#endif /* __CardGame_H__ */

