#ifndef BATTLE_H
#define BATTLE_H

#include <string>

#include "../TrainerInfo/Trainer.h"


class Battle {
public:
	Battle(Trainer* player, Trainer* opponent);
	Battle(Trainer* player, Pokemon* wild);



private:
	bool mIsWild;

	Trainer* mPlayer;
	Trainer* mOpponent;

	Pokemon* mPlayerPokemon;
	Pokemon* mOpponentPokemon;


};






#endif
