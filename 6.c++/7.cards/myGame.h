#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>

#include "cardGame.h"
#include "player.h"

class myGame_t: public cardGame_t
{
	public:
		myGame_t();
		virtual ~myGame_t (){};
		virtual void Play();
		
		//bool AddPlayer(const player_t* _player);
		//player_t* RemovePlayer(const player_t* _player);
		//player_t* RemovePlayer(unsigned int _index);
		
		void Print() const;

	protected:
		/* data */
		//std::vector<player_t*> m_players;
		//deck_t* m_deck;
		//hand_t m_board;
		//unsigned int m_playerCapacity;
		
	private:
		void InitializeGame();
		void DealCards();
		void AttackTurn(player_t* _player);
		bool DefendTurn(player_t* _player);
		bool IsPlayerWin(const player_t* _player) const;
		bool EndIfEnded(const player_t* _a, const player_t* _b) const;
		bool IsBoardFull() const;
		void ClearBoard();
};



#endif /* __MY_GAME_H__ */

