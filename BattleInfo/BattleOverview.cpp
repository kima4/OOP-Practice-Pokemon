#include <iostream>
#include <string>
#include <cstdlib>

#include "BattleOverview.h"

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









bool Battle::flee() {
	if (!mIsWild) {
		return false;
	}

	int playerSpeed = mPlayerPokemon->getStat(SPD);
	int wildSpeed = mOpponentPokemon->getStat(SPD);

	int escapeOdds = (((playerSpeed * 128) / wildSpeed) + 30 * mEscapeAttempts) % 256;
	int escapeVal = rand() % 256;

	if (escapeOdds > escapeVal) {
		return true;
	}
	return false;
}