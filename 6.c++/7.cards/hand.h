#ifndef __HAND_H__
#define __HAND_H__

#include <algorithm>    // std::stable_sort
#include <vector>		// std::vector
#include <iostream>     // std::ostream

#include "card.h"
#include "deck.h"

const unsigned int UNLIMITED = -1;

class hand_t
{
	public:
		hand_t(unsigned int _capacity = UNLIMITED);
		~hand_t (){};
		hand_t(const hand_t& _hand);
		hand_t& operator=(const hand_t& _hand);
		
		const card_t& operator[](unsigned int _index) const;
		bool InsertCard(const card_t& _card);
		bool GiveCard(unsigned int _index, hand_t& _hand);
		bool GiveCard(unsigned int _index, deck_t& _deck, unsigned int _position = 0); // 0 - top, 1 - end
		
		bool SetCapacity(unsigned int _newCapacity); //false if there are more elements than the new capacity
		unsigned int Size() const;
		bool IsEmpty() const;
		bool IsFull() const;
		
		int FindByRank(char _rank) const;
		int FindBySuit(char _suit) const;
		int Find(char _rank, char _suit) const;
		int FindGreaterThan(const card_t& _card) const;
		
		void EmptyHand();
		
		void PrintHand(std::ostream& _os) const;

	private:
		/* data */
		vector<card_t> m_cards;
		unsigned int m_capacity;
};

/*----------------------------------------*/

inline const card_t& hand_t::operator[](unsigned int _index) const
{
	return m_cards.at(_index);
}

inline unsigned int hand_t::Size() const
{
	return m_cards.size();
}

inline bool hand_t::IsEmpty() const
{
	return (0 == m_cards.size());
}

inline bool hand_t::IsFull() const
{
	return (m_capacity == m_cards.size());
}

inline void hand_t::EmptyHand()
{
	m_cards.clear();
}

#endif /* __HAND_H__ */

