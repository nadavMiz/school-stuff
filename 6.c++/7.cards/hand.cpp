#include <iostream>     // std::ostream

#include "hand.h"
#include "card.h"

hand_t::hand_t(unsigned int _capacity)
{
	m_capacity = _capacity;
}

/*--------------------------------------*/

hand_t::hand_t(const hand_t& _hand)
{
	m_cards = _hand.m_cards;
	m_capacity = _hand.m_capacity;
}

/*--------------------------------------*/

hand_t& hand_t::operator=(const hand_t& _hand)
{
	m_cards = _hand.m_cards;
	m_capacity = _hand.m_capacity;
	
	return *this;
}

/*--------------------------------------*/

bool hand_t::InsertCard(const card_t& _card)
{
	if(m_cards.size() == m_capacity)
	{
		return false;
	}
	
	for(unsigned int i = 0; i < m_cards.size(); ++i)
	{
		if(card_t::CompareCards(_card, m_cards.at(i)))
		{
			m_cards.insert(m_cards.begin() + i, _card);
			return true;
		}
	}
	
	m_cards.push_back(_card);
	return true;
}


/*-------------------------------------*/

bool hand_t::GiveCard(unsigned int _index, hand_t& _hand)
{
	unsigned int cardsNum = m_cards.size();
	
	if(0 == cardsNum || cardsNum < _index)
	{
		return false;
	}
	
	if(_hand.InsertCard(m_cards.at(_index)))
	{
		m_cards.erase(m_cards.begin() + _index);
		return true;
	}
	else
	{
		return false;
	}
}


bool hand_t::GiveCard(unsigned int _index, deck_t& _deck, unsigned int _position)
{
	unsigned int cardsNum = m_cards.size();
	
	if(0 == cardsNum || cardsNum < _index)
	{
		return false;
	}
	
	switch(_position)
	{
		case 0:
			_deck.InsertTop(m_cards.at(_index));
			break;
			
		case 1:
			_deck.InsertEnd(m_cards.at(_index));
			break;
			
		default:
			return false;
	}
	
	m_cards.erase(m_cards.begin() + _index);
	return true;
}

/*------------------------------------*/

bool hand_t::SetCapacity(unsigned int _newCapacity)
{
	if(m_cards.size() > _newCapacity)
	{
		return false;
	}
	
	m_capacity = _newCapacity;
	
	return true;
}

/*------------------------------------*/

int hand_t::FindByRank(char _rank) const
{	
	for(unsigned int i = 0; i < m_cards.size(); ++i)
	{
		if((m_cards.at(i)).GetRank() == _rank)
		{
			return i;
		}
	}
	
	return -1;
}

/*-----------------------------------*/

int hand_t::FindBySuit(char _suit) const
{
	unsigned int cardsNum = m_cards.size();
	
	for(unsigned int i = 0; i < cardsNum; ++i)
	{
		if((m_cards.at(i)).GetSuit() == _suit)
		{
			return i;
		}
	}
	
	return -1;
}

/*-----------------------------------*/

int hand_t::Find(char _rank, char _suit) const
{
	unsigned int cardsNum = m_cards.size();
	
	for(unsigned int i = 0; i < cardsNum; ++i)
	{
		if(((m_cards.at(i)).GetRank() == _rank) && ((m_cards.at(i)).GetSuit() == _suit))
		{
			return i;
		}
	}
	
	return -1;
}

/*-----------------------------------*/

int hand_t::FindGreaterThan(const card_t& _card) const
{
	unsigned int cardsNum = m_cards.size();
	
	for(unsigned int i = 0; i < cardsNum; ++i)
	{
		if(m_cards.at(i) > _card)
		{
			return i;
		}
	}
	
	return -1;
}

/*-----------------------------------*/

void hand_t::PrintHand(std::ostream& _os) const
{
	unsigned int cardsNum = m_cards.size();
	
	for(unsigned int i = 0; i < cardsNum; ++i)
	{
		_os << m_cards.at(i) << " ";
	}
	_os << std::endl;
}
