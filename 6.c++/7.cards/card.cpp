#include <iostream>

#include "card.h"

using namespace std;

char card_t::m_rankTable[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
char card_t::m_signTable[] = {'D', 'C', 'S', 'H'};

card_t::card_t(char _rank, char _suit)
{
	m_rank = ConvertRankToNum(_rank);
	m_suit = _suit;
}

card_t::card_t(unsigned int _rank, unsigned int _suit)
{
	m_rank = _rank;
	m_suit = m_signTable[_suit];
}

card_t::card_t(const card_t& _card)
{
	*this = _card;
}

card_t& card_t::operator=(const card_t& _card)
{
	m_rank = _card.m_rank;
	m_suit = _card.m_suit;
	
	return *this;
}

unsigned int card_t::ConvertRankToNum(char _rank)
{
	for(unsigned int i = 0; i < NUM_OF_NUMBERS; ++i)
	{
		if(m_rankTable[i] == _rank)
		{
			return i + FIRST_NUMBER;
		}
	}
	
	return 0;
}

const char* card_t::GetSuitGlyph() const
{
	switch(m_suit)
	{
		case 'D':
			return "\xe2\x99\xa2";
			
		case 'C':
			return "\xe2\x99\xa3";
			
		case 'S':
			return "\xe2\x99\xa4";
			
		case 'H':
			return "\xe2\x99\xa5";
			
		default:
			return "";
	}
}

char card_t::GetRank() const
{
	return m_rankTable[m_rank - FIRST_NUMBER];
}

ostream& operator<<(ostream& _os, const card_t& _card)
{
	_os << _card.GetRank() << _card.GetSuitGlyph();
	
	return _os;
}
