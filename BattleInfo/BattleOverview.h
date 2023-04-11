#ifndef BATTLEOVERVIEW_H
#define BATTLEOVERVIEW_H

#include <string>

#include "../TrainerInfo/Trainer.h"


class Battle {
public:
	Battle(Trainer* player, Trainer* opponent);
	Battle(Trainer* player, Pokemon* wild);

	/**
	 * Battle menu options 
	 */

	// fight
	Move** getMoves();
	double getStatChangeVal(bool isNormalStat, int statChange);
	double getAccuracy(Move* move);
	double calcAtkToDef(Category category, double crit);
	double stabBonus(Type moveType);
	double calcDamage(Move* move, double crit);
	double calcEffectiveness(Type moveType);
	double critBonus(bool highCritRatio);
	void doDamage(int damage);
	bool makeAttack(int moveSlot);
	
	// pokemon
	Pokemon** getPokemon();
	bool switchPokemon(Pokemon* switchIn);

	// bag


	// flee
	bool flee();

private:
	bool mIsWild;
	int mNumTurns;

	Trainer* mPlayer;
	Trainer* mOpponent;

	Pokemon* mPlayerPokemon;
	Pokemon* mOpponentPokemon;

	Pokemon* mAttackingPokemon;
	Pokemon* mDefendingPokemon;

	int mEscapeAttempts;

};






#endif
