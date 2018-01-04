#include <cstdlib> //std::rand

#include "hand.h"
#include "normalPlayer.h"

void normalPlayer_t::Play(hand_t& _board)
{
	if(_board.IsEmpty())
	{
		m_hand.GiveCard(std::rand() % m_hand.Size(), _board);
	}
	else
	{
		int PlayCardIndex = m_hand.FindGreaterThan(_board[0]);
		if(PlayCardIndex == -1)
		{
			_board.GiveCard(0, m_hand);
		}
		else
		{
			m_hand.GiveCard(PlayCardIndex, _board);
		}
	}
}
