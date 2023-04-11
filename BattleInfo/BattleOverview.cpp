#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>

#include "BattleOverview.h"
#include "../MiscInfo/TypeInteractions.h"

using namespace std;

Battle::Battle(Trainer* player, Trainer* opponent) : mPlayer(player), mOpponent(opponent) {
	mPlayerPokemon = player->getLead();
	mOpponentPokemon = opponent->getLead();
	mIsWild = false;
}

Battle::Battle(Trainer* player, Pokemon* wild) : mPlayer(player), mOpponentPokemon(wild) {
	mPlayerPokemon = player->getLead();
	mIsWild = true;
	mEscapeAttempts = 0;
}






Move** Battle::getMoves() {
	return mPlayerPokemon->getMoves();
}

double Battle::getStatChangeVal(bool isNormalStat, int statChange) {
	int baseVal;
	if (isNormalStat) {
		baseVal = 2;
	}
	else {
		baseVal = 3;
	}
	int change = baseVal + abs(statChange);

	if (statChange > 0) {
		return (double)change / (double)baseVal;
	}
	return (double)baseVal / (double)change;
}

double Battle::getAccuracy(Move* move) {
	int baseAccuracy = move->getBaseAccuracy();
	double attackerAccuracy = getStatChangeVal(false, mAttackingPokemon->getStatChange(ACC));
	double defenderEvasion = getStatChangeVal(false, mDefendingPokemon->getStatChange(EVA));
	return baseAccuracy * attackerAccuracy * defenderEvasion;
}

double Battle::calcAtkToDef(Category category, double crit) {
	Stat atkStat, defStat;
	if (category == PHYSICAL) {
		atkStat = ATK;
		defStat = DEF;
	}
	else {
		atkStat = SPATK;
		defStat = SPDEF;
	}
	int defStatChange = mDefendingPokemon->getStat(defStat);
	if (crit > 1 && defStatChange > 0) {
		defStatChange = 0;
	}

	double atk = mAttackingPokemon->getStat(atkStat) * getStatChangeVal(true, mAttackingPokemon->getStat(atkStat));
	double def = mDefendingPokemon->getStat(defStat) * getStatChangeVal(true, defStatChange);
	return atk / def;
}

double Battle::stabBonus(Type moveType) {
	Type* attackerTypes = mAttackingPokemon->getSpecies()->getTypes();

	if (moveType == attackerTypes[0] || moveType == attackerTypes[1]) {
		return 1.5;
	}
	return 1;
}

double Battle::calcDamage(Move* move, double crit) {
	double atkToDef = calcAtkToDef(move->getCategory(), crit);
	double damageCore = ((((2 * (double)mAttackingPokemon->getLevel()) / 5) + 2) * (double)move->getBasePower() * atkToDef) / 50;
	Type moveType = move->getType();
	
	double damage = (damageCore + 2) * stabBonus(moveType) * crit;

	return round(damage);
}

double Battle::calcEffectiveness(Type moveType) {
	Type* defenderTypes= mDefendingPokemon->getSpecies()->getTypes();

	return getMultiplier(moveType, defenderTypes[0], defenderTypes[1]);
}

double Battle::critBonus(bool highCritRatio) {
	int critTable[5] = { 3, 6, 12, 16, 24 };
	int critLevel = mAttackingPokemon->getStatChange(CRIT);
	if (highCritRatio) {
		critLevel++;
	}
	if (critLevel > 4) {
		critLevel = 4;
	}
	int critChance = critTable[critLevel];
	int critVal = rand % 48;

	if (critChance <= critVal) {
		return 1;
	}
	return 2;
}

void Battle::doDamage(int damage) {
	int currentHP = mDefendingPokemon->getCurrentHP();
	int resultingHP = currentHP - damage;
	if (resultingHP < 0) {
		resultingHP = 0;
	}
	mDefendingPokemon->setCurrentHP(resultingHP);
}

bool Battle::makeAttack(int moveSlot) {
	if (!(mAttackingPokemon->getMovePP(moveSlot) > 0)) {
		return false;
	}
	Move* move = mAttackingPokemon->getMove(moveSlot);

	double hitChance = getAccuracy(move);
	int hitVal = rand() % 101;
	if (hitChance < hitVal) {
		// attack missed
		return true;
	}
	double damageMultiplier = calcEffectiveness(move->getType());
	if (damageMultiplier == 0) {
		// attack ineffective
		return true;
	}

	double critMultiplier = critBonus(false); //TODO: implement moves with special effects

	int damage = round(calcDamage(move, critMultiplier) * damageMultiplier);
	
	doDamage(damage);

	mAttackingPokemon->decMovePP(moveSlot);

	return true;
}




Pokemon** Battle::getPokemon() {
	return mPlayer->getPokemon();
}

bool Battle::switchPokemon(Pokemon* switchIn) {
	if (switchIn->getCurrentHP() == 0) {
		return false;
	}
	mPlayerPokemon = switchIn;
	return true;
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
	mEscapeAttempts++;
	return false;
}