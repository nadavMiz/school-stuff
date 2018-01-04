#include <iostream>
#include <vector>
#include <ctime> //std::time

#include "card.h"
#include "deck.h"
#include "hand.h"
#include "normalPlayer.h"
#include "myGame.h"

using namespace std;

int main()
{
	myGame_t game;
	srand(std::time(0));
	game.Play();
	
	return 1;
}
