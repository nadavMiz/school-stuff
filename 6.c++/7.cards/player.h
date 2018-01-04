#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>

#include "hand.h"
#include "card.h"

class player_t
{
	public:
		player_t(const char* _name = "", unsigned int _cardCapacity = UNLIMITED);
		virtual ~player_t (){};
		
		virtual void Play(hand_t& _board) = 0;
		
		bool TakeCard(const card_t& _card);
		bool TakeCard(hand_t& _board, unsigned int _index);
		bool GiveCard(hand_t& _hand);
		bool GiveCard(deck_t& _deck, unsigned int _position = 0);
		const hand_t& GetHand() const;
		void Print(std::ostream& _os) const;
		const char* GetName() const;
		void ClearHand();

	protected:
		/* data */
		hand_t m_hand;
		char* m_name;
};

inline bool player_t::TakeCard(const card_t& _card)
{
	return m_hand.InsertCard(_card);
}

inline bool player_t::TakeCard(hand_t& _board, unsigned int _index)
{
	return _board.GiveCard(_index, m_hand);
}

inline bool player_t::GiveCard(hand_t& _hand)
{
	return  m_hand.GiveCard(0, _hand);
}

inline bool player_t::GiveCard(deck_t& _deck, unsigned int _position)
{
	return  m_hand.GiveCard(0, _deck, _position);
}

inline const hand_t& player_t::GetHand() const
{
	return m_hand;
}

inline void player_t::Print(std::ostream& _os) const
{
	_os << m_name << ": ";
	m_hand.PrintHand(_os);
}

inline const char* player_t::GetName() const
{
	return m_name;
}

inline void player_t::ClearHand()
{
	m_hand.EmptyHand();
}

#endif /* __PLAYER_H__ */

