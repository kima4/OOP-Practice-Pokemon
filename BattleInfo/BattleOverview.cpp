#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <vector>

#include "BattleOverview.h"
#include "../MiscInfo/TypeInteractions.h"

using namespace std;

/* ----------------------------------------------------------------
 *
 * 
 * 
 *                        BattleOverview
 * 
 * 
 * 
 * ----------------------------------------------------------------*/


BattleOverview::BattleOverview() {
	mTurnNum = 0;
	resetStatChanges(true);
	resetStatChanges(false);
	mEscapeAttempts = 0;
}

BattleOverview::BattleOverview(Trainer* player, Pokemon* wild) : BattleOverview() {
	mTrainers.push_back(player);
	mPlayerPokemon = player->getLead();
	mOpponentPokemon = wild;
	mIsWild = true;
	
}

BattleOverview::BattleOverview(Trainer* player, Trainer* opponent) : BattleOverview() {
	mTrainers.push_back(player);
	mTrainers.push_back(opponent);
	mPlayerPokemon = player->getLead();
	mOpponentPokemon = opponent->getLead();
	mIsWild = false;
}


void BattleOverview::battle() {
	while (!isFinished()) {
		cout << "Player Action:" << endl;
		Action* playerAction = selectAction(true);
		while (playerAction->getActionType() == MISTAKE) {
			delete playerAction;
			playerAction = selectAction(true);
		}
		cout << "Opponent Action:" << endl;
		Action* opponentAction = selectAction(false);
		while (opponentAction->getActionType() == MISTAKE) {
			delete opponentAction;
			opponentAction = selectAction(false);
		}
		if (determineOrder(playerAction, opponentAction)) {
			battleStep(playerAction, opponentAction);
		}
		else {
			battleStep(opponentAction, playerAction);
		}
	}
}

void BattleOverview::battleStep(Action* action1, Action* action2) {
	performAction(action1);
	mActionHistory.push_back(action1);
	if (isFinished()) { //TODO create methdo for determining if pokemon fainted, delete second action if so, and replace it with a switch in action
		return;
	}
	performAction(action2);
	mActionHistory.push_back(action2);
	return;
}

Action* BattleOverview::selectAction(bool isPlayer) {
	cout << "1. Fight" << endl;
	cout << "2. Bag" << endl;
	cout << "3. Switch" << endl;
	cout << "4. Flee" << endl;

	int choice = selectOption(1, 4);
	
	return createAction(isPlayer, choice);
}

int BattleOverview::selectOption(int min, int max) {
	int choice;
	cin >> choice;
	while (choice < min || choice > max) {
		cout << "Invalid choice. Choose again: " << endl;
		cin >> choice;
	}
	return choice;
}

Action* BattleOverview::createAction(bool isPlayer, int choice) {
	
	switch (choice) {
	case 1:
	{
		Fight* action = new Fight(*this, isPlayer);
		if (action->selectMove()) {
			action->print();
			return action;
		}
		break;
	}
	case 2:
		//return new Bag();
	case 3:
		return new Switch(*this, isPlayer);
	case 4:
		if (mIsWild) {
			return new Flee(*this, isPlayer);
		}
		cout << "There's no running from a trainer battle!" << endl;
		break;
	}
	//cout << "Something went wrong in BattleOverview::selectAction()." << endl;
	return new Action(*this, isPlayer);
}

Action* BattleOverview::getLastAction() {
	return mActionHistory.back();
}

// true if player goes first
bool BattleOverview::attackOrder(Fight* playerAction, Fight* opponentAction) {
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
bool BattleOverview::checkSpeeds() {
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
bool BattleOverview::determineOrder(Action* playerAction, Action* opponentAction) {
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
void BattleOverview::performAction(Action* action) {
	action->execute();
}

Trainer* BattleOverview::getTrainer(bool isPlayer) {
	if (isPlayer) {
		return mTrainers[0];
	}
	return mTrainers[1];
}

Pokemon* BattleOverview::getPlayerPokemon() {
	return mPlayerPokemon;
}

Pokemon* BattleOverview::getOpponentPokemon() {
	return mOpponentPokemon;
}

int BattleOverview::getStatChange(bool isPlayer, Stat stat) {
	if (isPlayer) {
		return mPStatChanges[stat];
	}
	return mOStatChanges[stat];
}

void BattleOverview::setStatChange(bool isPlayer, Stat stat, int statChange) {
	if (statChange > 6) { // TODO implement can't go higher/lower ability
		statChange = 6;
	}
	if (statChange < -6) {
		statChange = -6;
	}

	if (isPlayer) {
		mPStatChanges[stat] = statChange;
	}
	else {
		mOStatChanges[stat] = statChange;
	}
}

void BattleOverview::addStatChanges(bool isPlayer, int* statChanges) {
	for (int i = ATK; i != NUM_STAT_CHANGES; i++) {
		setStatChange(isPlayer, (Stat)i, statChanges[i] + getStatChange(isPlayer, (Stat)i));
	}
}

void BattleOverview::resetStatChanges(bool isPlayer) {
	for (int i = ATK; i != NUM_STAT_CHANGES; i++) {
		setStatChange(isPlayer, (Stat)i, 0);
	}
}

bool BattleOverview::isWild() {
	return mIsWild;
}

int BattleOverview::getTurnNum() {
	return mTurnNum;
}

int BattleOverview::getEscapeAttempts() {
	return mEscapeAttempts;
}

void BattleOverview::incEscapeAttempts() {
	mEscapeAttempts++;
}


// true if battle is over
bool BattleOverview::isFinished() {
	// check if either side is out of pokemon
	for (int i = 0; i < mTrainers.size(); i++) {
		if (mTrainers[i]->getNumUsablePokemon() == 0) {
			return true;
		}
	}

	// check if wild pokemon if fainted ******TODO add captured
	if (mIsWild && mOpponentPokemon->isFainted()) {
		return true;
	}

	// check if someone fled successfully
	if (mActionHistory.size() > 0) {
		Action* lastAction = getLastAction();
		if (lastAction->getActionType() == FLEE) {
			if (lastAction->getParameter() > 0) {
				return true;
			}
		}
	}

	return false;
}



/* ----------------------------------------------------------------
 *
 *
 *
 *                            Action
 *
 *
 *
 * ----------------------------------------------------------------*/

Action::Action(BattleOverview& battle, bool isPlayer) : mIsPlayer(isPlayer), mBattle(battle) {
	setActionType(MISTAKE);
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

bool Action::isPlayerAction() {
	return mIsPlayer;
}

BattleOverview& Action::getBattleRef() {
	return mBattle;
}

void Action::setParameter(int val) {
	mParameter = val;
}

int Action::getParameter() {
	return mParameter;
}

void Action::print() {
	cout << "-------------------------" << endl;
	cout << "Mistakes were made." << endl;
	cout << "-------------------------" << endl;
}

/* ----------------------------------------------------------------
 *
 *
 *
 *                            Fight
 *
 *
 *
 * ----------------------------------------------------------------*/

Fight::Fight(BattleOverview& battle, bool isPlayer) : Action(battle, isPlayer) {
	setActionType(FIGHT);
	if (isPlayer) {
		mAttacker = getBattleRef().getPlayerPokemon();
		mDefender = getBattleRef().getOpponentPokemon();
	}
	else {
		mAttacker = getBattleRef().getOpponentPokemon();
		mDefender = getBattleRef().getPlayerPokemon(); 
	}
}

Fight::Fight(BattleOverview& battle, bool isPlayer, Move* move) : Action(battle, isPlayer) {
	setActionType(FIGHT);
	mMove = move;
	if (isPlayer) {
		mAttacker = getBattleRef().getPlayerPokemon();
		mDefender = getBattleRef().getOpponentPokemon();
	}
	else {
		mAttacker = getBattleRef().getOpponentPokemon();
		mDefender = getBattleRef().getPlayerPokemon();
	}
}

int Fight::getPriority() {
	return mMove->getPriority(); 
}

// false if no move selected
bool Fight::selectMove() {
	vector<Move*> moves = mAttacker->getMoves();
	vector<int> pps = mAttacker->getMovesPP();

	for (int i = 0; i < moves.size(); i++) {
		cout << i + 1 << ":" << endl;
		moves[i]->print();
		cout << "  Current PP: " << pps[i] << endl;
	}
	cout << "Press 0 to return to previous menu." << endl;

	int choice;
	cin >> choice;
	while (choice < 1 || choice > moves.size() || pps[choice - 1] < 1) {
		if (choice == 0) {
			return false;
		}
		cout << "Invalid choice. Choose again: " << endl;
		cin >> choice;
	}

	mMove = moves[choice - 1];

	return true;
}

int Fight::getAttackerStatChange(Stat stat) {
	return getBattleRef().getStatChange(isPlayerAction(), stat);
}

int Fight::getDefenderStatChange(Stat stat) {
	return getBattleRef().getStatChange(!isPlayerAction(), stat);
}

double Fight::calcStatChangeMult(Stat stat, int statChange) {
	double baseVal;
	if (stat == EVA || stat == ACC) {
		baseVal = 3;
	}
	else {
		baseVal = 2;
	}
	double change = baseVal + abs(statChange);

	if (statChange > 0) {
		return change / baseVal;
	}
	return baseVal / change;
}

double Fight::calcAccuracy(int acc) {
	double attackerAccuracy = calcStatChangeMult(ACC, getAttackerStatChange(ACC));
	double defenderEvasion = calcStatChangeMult(EVA, getDefenderStatChange(EVA));
	return (double)acc * attackerAccuracy * defenderEvasion;
}

double Fight::calcEffectiveness(Type moveType) {
	Type* defenderTypes = mDefender->getSpecies()->getTypes();
	return getMultiplier(moveType, defenderTypes[0], defenderTypes[1]);
}

double Fight::calcCrit(int critRatio) {
	int critTable[5] = {3, 6, 12, 16, 24};
	int critLevel = getAttackerStatChange(CRIT);
	if (critRatio < 0) {
		return 1;
	}
	else if (critRatio > 0) {
		critLevel++;
	}
	if (critLevel > 4) {
		critLevel = 4;
	}
	
	int critChance = critTable[critLevel];
	int critVal = rand() % 48;
	
	if (critChance < critVal) {
		return 1;
	}
	return 2;
}

double Fight::calcAtkToDef(double crit) {
	Stat atkStat, defStat;
	if (mMove->getCategory() == PHYSICAL) {
		atkStat = ATK;
		defStat = DEF;
	}
	else {
		atkStat = SPATK;
		defStat = SPDEF;
	}
	int defStatChange = getDefenderStatChange(defStat);
	if (crit > 1 && defStatChange > 0) {
		defStatChange = 0;
	}

	//cout << "RAW ATTACK: " << mAttacker->getStat(atkStat) << endl;
	//cout << "RAW DEFENSE: " << mDefender->getStat(defStat) << endl;

	double atk = mAttacker->getStat(atkStat) * calcStatChangeMult(atkStat, getAttackerStatChange(atkStat));
	double def = mDefender->getStat(defStat) * calcStatChangeMult(defStat, defStatChange);

	//cout << "ATTACK: " << atk << endl;
	//cout << "DEFENSE: " << def << endl;

	return atk / def;
}

double Fight::calcSTAB(Type moveType) {
	Type* attackerTypes = mAttacker->getSpecies()->getTypes();
	if (moveType == attackerTypes[0] || moveType == attackerTypes[1]) {
		//cout << "Move has stab!" << endl;
		return 1.5;
	}
	return 1;
}

double Fight::calcDamage(double crit) {
	double atkToDef = calcAtkToDef(crit);
	double stabBonus = calcSTAB(mMove->getType());

	double damageCore = ((((2 * mAttacker->getLevel()) / 5) + 2) * mMove->getBasePower() * atkToDef) / 50;
	//cout << "DAMAGE CORE: " << damageCore << endl;

	double damage = (damageCore + 2) * stabBonus * crit;
	//cout << "DAMAGE: " << damage << endl;

	return damage;
}

void Fight::doDamage(int damage) {
	if (damage > mDefender->getCurrentHP()) {
		damage = mDefender->getCurrentHP();
	}

	setParameter(damage); // storing amount of damage done
	mDefender->takeDamage(damage);
}

void Fight::makeAttack() {
	double hitChance = calcAccuracy(mMove->getBaseAccuracy());
	int hitVal = rand() % 100;
	if (hitChance < hitVal) {
		cout << "Attack missed!" << endl;
		return;
	}
	
	if (mMove->getCategory() != STATUS) {
		double damageMultiplier = calcEffectiveness(mMove->getType());
		if (damageMultiplier == 0) {
			cout << "Attack does not affect opponent!" << endl;
			return;
		}
		//cout << "DAMAGE MULTIPLIER: " << damageMultiplier << endl;

		double critMultiplier = calcCrit(mMove->getCritRate());

		int damage = round(calcDamage(critMultiplier) * damageMultiplier);

		doDamage(damage);
		cout << "The attack did " << damage << " damage!" << endl;
	}
	//TODO status stuff

}

void Fight::execute() {
	makeAttack();
}

void Fight::print() {
	cout << "-------------------------" << endl;
	cout << "Fight Action" << endl;
	cout << "  Attacking Pokemon: " << endl;
	mAttacker->print();
	cout << "  Defending Pokemon: " << endl;
	mDefender->print();
	cout << "  Move Used: " << mMove->getMoveName() << endl;
	cout << "-------------------------" << endl;
}

/* ----------------------------------------------------------------
 *
 *
 *
 *                             Bag
 *
 *
 *
 * ----------------------------------------------------------------*/


/* ----------------------------------------------------------------
 *
 *
 *
 *                           Switch
 *
 *
 *
 * ----------------------------------------------------------------*/

Switch::Switch(BattleOverview& battle, bool isPlayer) : Action(battle, isPlayer) {
	setActionType(SWITCH);
}


/* ----------------------------------------------------------------
 *
 *
 *
 *                            Flee
 *
 *
 *
 * ----------------------------------------------------------------*/
 
Flee::Flee(BattleOverview& battle, bool isPlayer) : Action(battle, isPlayer) {
	setActionType(FLEE);
}

//bool Flee::wasSuccessful() {
//	return mSuccess;
//}

int Flee::attemptEscape() {
	int playerSpd = getBattleRef().getPlayerPokemon()->getStat(SPD);
	int wildSpd = getBattleRef().getOpponentPokemon()->getStat(SPD);

	if (playerSpd > wildSpd) {
		cout << "Escaped from battle!" << endl;
		return 1;
	}

	int escapeOdds = (((playerSpd * 128) / wildSpd) + 30 * getBattleRef().getEscapeAttempts()) % 256;
	int escapeVal = rand() % 256;

	if (escapeOdds > escapeVal) {
		cout << "Escaped from battle!" << endl;
		return 1;
	}

	getBattleRef().incEscapeAttempts();
	cout << "Couldn't get away!" << endl;
	return -1;
}

void Flee::execute() {
	setParameter(attemptEscape());
}







