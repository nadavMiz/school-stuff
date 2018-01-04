#ifndef __CARD_H__
#define __CARD_H__

#define NUM_OF_NUMBERS 13
#define NUM_OF_SIGNES 4

#include <iostream>

using namespace std;

const unsigned int FIRST_NUMBER = 2;

class card_t
{
	public:
		card_t (char _rank, char _suit);
		card_t (unsigned int _rank, unsigned int _suit);
		~card_t (){};
		card_t(const card_t& _card);
		card_t& operator=(const card_t& _card);
		bool operator<(const card_t& _card) const;
		bool operator<=(const card_t& _card) const;
		bool operator>(const card_t& _card) const;
		bool operator>=(const card_t& _card) const;
		bool operator==(const card_t& _card) const;
		bool operator!=(const card_t& _card) const;
		
		char GetSuit() const;
		char GetRank() const;
		unsigned int GetValue() const;
		const char* GetSuitGlyph() const;

		/* static functions */
		static bool CompareCards(const card_t& _a, const card_t& _b); //for sorting

	private:
		/* data */
		unsigned int m_rank;
		char m_suit;
		
		/*static data*/
		static char m_rankTable[NUM_OF_NUMBERS];
		static char m_signTable[NUM_OF_SIGNES];
		
	private:
		unsigned int ConvertRankToNum(const char _rank);
};

ostream& operator<<(ostream& _os, const card_t& _card);

/*------------------------------------------------------*/

inline unsigned int card_t::GetValue() const
{
	return m_rank - 2;
}

inline char card_t::GetSuit() const
{
	return m_suit;
}

inline bool card_t::operator==(const card_t& _card) const
{
	return ((m_suit == _card.m_suit) && (m_rank == _card.m_rank));
}

inline bool card_t::operator>(const card_t& _card) const
{
	return ((m_suit == _card.m_suit) && (m_rank > _card.m_rank));
}

inline bool card_t::operator>=(const card_t& _card) const
{
	return ((m_suit == _card.m_suit) && (m_rank >= _card.m_rank));
}

inline bool card_t::operator<(const card_t& _card) const
{
	return !(*this >= _card);
}

inline bool card_t::operator<=(const card_t& _card) const
{
	return !(*this > _card);
}

inline bool card_t::operator!=(const card_t& _card) const
{
	return !(*this == _card);
}


inline bool card_t::CompareCards(const card_t& _a, const card_t& _b)
{
	return ((_a.m_suit < _b.m_suit) || ((_a.m_suit == _b.m_suit) && (_a.m_rank < _b.m_rank)));
}

#endif /* __CARD_H__ */

