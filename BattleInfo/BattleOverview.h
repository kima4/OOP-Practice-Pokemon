#ifndef BATTLEOVERVIEW_H
#define BATTLEOVERVIEW_H

#include <string>

#include "../TrainerInfo/Trainer.h"


class Battle {
public:
	Battle(Trainer* player, Trainer* opponent);
	Battle(Trainer* player, Pokemon* wild);



	bool flee();

private:
	bool mIsWild;

	Trainer* mPlayer;
	Trainer* mOpponent;

	Pokemon* mPlayerPokemon;
	Pokemon* mOpponentPokemon;

	int mEscapeAttempts;

};






#endif
