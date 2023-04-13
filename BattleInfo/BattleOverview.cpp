#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <vector>

#include "BattleOverview.h"
#include "../MiscInfo/TypeInteractions.h"

using namespace std;

BattleOverview::BattleOverview(Trainer* player, Pokemon* wild) {
	mTrainers.push_back(player);
	startBattle(player->getLead(), wild);
	mTurnNum = 0;
}


BattleOverview::BattleOverview(Trainer* player, Trainer* opponent) {
	mTrainers.push_back(player);
	mTrainers.push_back(opponent);
	startBattle(player->getLead(), opponent->getLead());
	mTurnNum = 0;
}


void BattleOverview::startBattle(Pokemon* pPokemon, Pokemon* oPokemon) {
	mBattle = new Battle(pPokemon, oPokemon);
}


void BattleOverview::battle() {
	while (!isFinished()) {
		Action* playerAction = selectAction(true);
		Action* opponentAction = selectAction(false);

		if (mBattle->determineOrder(playerAction, opponentAction)) {
			battleStep(playerAction, opponentAction);
		}
		else {
			battleStep(opponentAction, playerAction);
		}
	}
}

void BattleOverview::battleStep(Action* action1, Action* action2) {
	mBattle->performAction(action1);
	mActionHistory.push_back(action1);
	if (isFinished()) {
		return;
	}
	mBattle->performAction(action2);
	mActionHistory.push_back(action2);
	return;
}

Action* BattleOverview::selectAction(bool isPlayer) {
	int choice;
	cin >> choice;
	while (choice < 1 || choice > 4) {
		cout << "Invalid choice. Choose again: " << endl;
		cin >> choice;
	}
	switch (choice) {
	case 1:
		return new Fight(isPlayer);
	case 2:
		//return new Bag();
	case 3:
		return new Switch(isPlayer);
	case 4:
		return new Flee(isPlayer);
	}
	cout << "Something went wrong in BattleOverview::selectAction()." << endl;
	return new Action(isPlayer);
}


Action* BattleOverview::getLastAction() {
	return mActionHistory.back();
}

// true if battle is over
bool BattleOverview::isFinished() {
	// check if either side is out of pokemon
	for (int i = 0; i < mTrainers.size(); i++) {
		if (mTrainers[i]->getNumUsablePokemon() == 0) {
			return true;
		}
	}

	// check if someone fled successfully
	Action* lastAction = getLastAction();
	if (lastAction->getActionType() == FLEE) {
		Flee* fleeAction = dynamic_cast<Flee*>(getLastAction());
		if (fleeAction->wasSuccessful()) {
			return true;
		}
	}

	return false;
}



Action::Action(bool isPlayer) : mIsPlayer(isPlayer) {

}

ActionType Action::getActionType() {
	return mActionType;
}

void Action::setActionType(ActionType actionType) {
	mActionType = actionType;
}

void Action::execute() {
	cout << "An action is executed" << endl;
}



Fight::Fight(bool isPlayer) : Action(isPlayer) {

}

Fight::Fight(bool isPlayer, Move* move) : Action(isPlayer) {
	mMove = move;
}

int Fight::getPriority() {
	return mMove->getPriority();
}




Switch::Switch(bool isPlayer) : Action(isPlayer) {
	setActionType(SWITCH);
}

Flee::Flee(bool isPlayer) : Action(isPlayer) {
	setActionType(FLEE);
}

bool Flee::wasSuccessful() {
	return mSuccess;
}

Battle::Battle(Pokemon* pPokemon, Pokemon* oPokemon) : mPlayerPokemon(pPokemon), mOpponentPokemon(oPokemon) {

}

// true if player goes first
bool Battle::attackOrder(Fight* playerAction, Fight* opponentAction) {
	int playerPriority = playerAction->getPriority();
	int opponentPriority = opponentAction->getPriority();
	if (playerPriority > opponentPriority) {
		return true;
	}
	else if (opponentPriority > playerPriority) {
		return false;
	}
	return checkSpeeds();
}

// true if player goes first
bool Battle::checkSpeeds() {
	int playerSpeed = mPlayerPokemon->getStat(SPD);
	int opponentSpeed = mOpponentPokemon->getStat(SPD);
	if (playerSpeed > opponentSpeed) {
		return true;
	}
	else if (playerSpeed > opponentSpeed) {
		return false;
	}
	int cointoss = rand() % 2;
	if (cointoss == 0) {
		return true;
	}
	return false;
}

// true if player goes first
bool Battle::determineOrder(Action* playerAction, Action* opponentAction) {
	ActionType pActionType = playerAction->getActionType();
	ActionType oActionType = opponentAction->getActionType();

	switch (pActionType) {
	case BAG:
	case SWITCH:
	case FLEE:
		return true;
	}
	switch (oActionType) {
	case BAG:
	case SWITCH:
	case FLEE:
		return false;
	}
	Fight* playerAttack = dynamic_cast<Fight*>(playerAction);
	Fight* opponentAttack = dynamic_cast<Fight*>(opponentAction);
	return attackOrder(playerAttack, opponentAttack);
}

// 
void Battle::performAction(Action* action) {

}



/*Battle::Battle(Trainer* player, Trainer* opponent) : mPlayer(player), mOpponent(opponent) {
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

bool Battle::checkAttackUsability(int moveSlot) {
	if (!(mAttackingPokemon->getMovePP(moveSlot) > 0)) {
		return false;
	}
	return true;
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

double Battle::critBonus(int critRatio) {
	int critTable[5] = { 3, 6, 12, 16, 24 };
	int critLevel = mAttackingPokemon->getStatChange(CRIT);
	if (critRatio > 0) {
		critLevel++;
	}
	else if (critRatio < 0) {
		return 1;
	}
	if (critLevel > 4) {
		critLevel = 4;
	}
	int critChance = critTable[critLevel];
	int critVal = rand() % 48;

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
	Move* move = mAttackingPokemon->getMove(moveSlot);

	double hitChance = getAccuracy(move);
	int hitVal = rand() % 101;
	if (hitChance < hitVal) {
		// attack missed
		return false;
	}

	double damageMultiplier = calcEffectiveness(move->getType());
	if (damageMultiplier == 0) {
		// attack ineffective
		return false;
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
}*/


