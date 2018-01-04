#ifndef __NORMAL_PLAYER_H__
#define __NORMAL_PLAYER_H__

#include "player.h"

class normalPlayer_t: public player_t
{
	public:
		normalPlayer_t(const char* _name) : player_t(_name){};
		virtual ~normalPlayer_t (){};
		
		virtual void Play(hand_t& _board);
		
		//bool TakeCard(card_t& _card);
		//bool GiveCard(hand_t& _hand);
		//bool GiveCard(deck_t& _deck, unsigned int _position);

	private:
		/* data */
		//hand_t m_hand;
};

#endif /* __NORMAL_PLAYER_H__ */

