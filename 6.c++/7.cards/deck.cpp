#include <stddef.h>
#include <iostream>

#include "deck.h"
#include "card.h"

const unsigned int NUM_CARDS = 52;

using namespace std;

deck_t::deck_t()
{	
	Refill();
}

/*-------------------------------------------------*/

card_t deck_t::Draw()
{
	card_t card = m_deck.at(m_deck.size() - 1);
	m_deck.pop_back();
	return card;
}

/*--------------------------------------------------*/

void deck_t::Refill()
{
	m_deck.clear();
	
	for(unsigned int suit = 0; suit < NUM_OF_SIGNES; ++suit)
	{
		for(unsigned int num = 0; num < NUM_OF_NUMBERS; ++num)
		{
			card_t newCard(num + FIRST_NUMBER, suit);
			InsertTop(newCard);
		}
	}
}

/*--------------------------------------------------*/

void deck_t::PrintDeck(ostream& _os)
{
	size_t deckSize = m_deck.size();
	for(size_t i = 0; i < deckSize; ++i)
	{
		_os << (m_deck.at(i)) << " ";
		if((i % 13) == 12)
		{
			_os << endl;
		}
	}
	_os << endl;
}
