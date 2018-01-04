#include <iostream>

#include "myGame.h"
#include "player.h"
#include "normalPlayer.h"

static const unsigned int NUM_PLAYERS = 4;
const unsigned int CARDS_PER_PLAYER = 13;

myGame_t::myGame_t(): cardGame_t(NUM_PLAYERS, 2)
{
	m_players.push_back(new normalPlayer_t("nadav1"));
	m_players.push_back(new normalPlayer_t("nadav2"));
	m_players.push_back(new normalPlayer_t("nadav3"));
	m_players.push_back(new normalPlayer_t("nadav4"));
	
	m_deck = new deck_t;
	if(0 == m_deck)
	{
		//TODO something
	}
}

void myGame_t::DealCards()
{
	unsigned int i = 0;
	while(!m_deck->IsEmpty())
	{
		m_players[i]->TakeCard(m_deck->Draw());
		
		++i %= NUM_PLAYERS;
	}
}

void myGame_t::InitializeGame()
{
	for(unsigned int i = 0; i < NUM_PLAYERS; ++i)
	{
		m_players[i]->ClearHand();
	}
	
	m_deck->Refill();
	m_deck->Shuffle();
	
	DealCards();
}

void myGame_t::Play()
{
	unsigned int currentPlayer = 0;
	unsigned int prevPlayer = 3;
	bool IsRunning = true;
	
	InitializeGame();
	
	while(IsRunning)
	{
		AttackTurn(m_players[currentPlayer]);
		prevPlayer = currentPlayer;
		++currentPlayer %= NUM_PLAYERS;
		
		if(!DefendTurn(m_players[currentPlayer]))
		{
			++currentPlayer %= NUM_PLAYERS;
		}
		IsRunning = EndIfEnded(m_players[prevPlayer], m_players[currentPlayer]);
	}
}

void myGame_t::AttackTurn(player_t* _player)
{
	_player->Play(m_board);
}

bool myGame_t::DefendTurn(player_t* _player)
{
	_player->Play(m_board);
	
	if(m_board.IsFull())
	{
		ClearBoard();
		return true;
	}
	
	return false;
}

void myGame_t::ClearBoard()
{
	m_board.GiveCard(1, *m_deck);
	m_board.GiveCard(0, *m_deck);
}

bool myGame_t::EndIfEnded(const player_t* _a, const player_t* _b) const
{
	bool isAwin = _a->GetHand().IsEmpty();
	bool isBwin = _b->GetHand().IsEmpty();
	
	if(isAwin && isBwin)
	{
		Print();
		cout << _a->GetName() << " and " << _b->GetName() << "have won" << endl;
		return false;
	}
	else if(isAwin)
	{
		Print();
		cout << _a->GetName() << " has won" << endl;
		return false;
	}
	else if(isBwin)
	{
		Print();
		cout << _b->GetName() << " has won" << endl;
		return false;
	}
	return true;
}

void myGame_t::Print() const
{
	for(unsigned int i = 0; i < NUM_PLAYERS; ++i)
	{
		m_players[i]->Print(cout);
	}
	cout << "board: ";
	m_board.PrintHand(cout);
	cout << std::endl;
}
