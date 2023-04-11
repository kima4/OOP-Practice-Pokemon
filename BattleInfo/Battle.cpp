#include <iostream>
#include <string>

#include "Battle.h"

using namespace std;

Battle::Battle(Trainer* player, Trainer* opponent) : mPlayer(player), mOpponent(opponent) {
	mPlayerPokemon = player->getPokemon()[0];
	mOpponentPokemon = opponent->getPokemon()[0];
	mIsWild = false;
}

Battle::Battle(Trainer* player, Pokemon* wild) : mPlayer(player), mOpponentPokemon(wild) {
	mPlayerPokemon = player->getPokemon()[0];
	mIsWild = true;
}




