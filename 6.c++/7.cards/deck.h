#ifndef __DECK_H__
#define __DECK_H__

#include <vector>
#include <iostream>
#include <algorithm> // shuffle

#include "card.h"

class deck_t
{
	public:
		deck_t ();
		virtual ~deck_t (){};
		deck_t(deck_t& _deck);
		deck_t& operator=(deck_t& _deck);
		
		void Shuffle();
		card_t Draw();
		void Refill();
		void InsertTop(const card_t& _card);
		void InsertEnd(const card_t& _card);
		bool IsEmpty();
		void PrintDeck(ostream& _os); // for debugging

	private:
		/* data */
		std::vector<card_t> m_deck;
};

inline void deck_t::Shuffle()
{
	std::random_shuffle(m_deck.begin(), m_deck.end());
}

inline void deck_t::InsertTop(const card_t& _card)
{
	m_deck.push_back(_card);
}

inline void deck_t::InsertEnd(const card_t& _card)
{
	m_deck.insert(m_deck.begin(), _card);
}

inline bool deck_t::IsEmpty()
{
	return (0 == m_deck.size());
}

#endif /* __DECK_H__ */

