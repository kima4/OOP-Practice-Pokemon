#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <algorithm>

#include "Action.h"
#include "../MiscInfo/TypeInteractions.h"


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
	mTurnNum = mBattle.getTurnNum();
	mActionNum = 0;
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

int Action::getTurnNum() {
	return mTurnNum;
}

int Action::getActionNum() {
	return mActionNum;
}

void Action::setActionNum(int actionNum) {
	mActionNum = actionNum;
}

int Action::selectOption(int min, int max, bool back) {
	int choice;
	cout << "Select an option: ";
	cin >> choice;
	while (choice < min || choice > max) {
		if (back && choice == 0) {
			return 0;
		}
		cout << "Invalid choice. Choose again: ";
		cin >> choice;
	}
	return choice;
}

void Action::printPreview() {
	cout << "-------------------" << endl;
	cout << "Mistakes were made." << endl;
	cout << "-------------------" << endl;
}

void Action::print() {
	cout << "===================" << endl;
	cout << "Mistakes were made." << endl;
	cout << "===================" << endl;
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
	setActionNum(getBattleRef().getLastAction()->getActionNum() + 1);
	mAttacker = getBattleRef().getPokemon(isPlayer);
	//mDefender = getBattleRef().getPokemon(!isPlayer);
}

Fight::Fight(BattleOverview& battle, bool isPlayer, Move* move) : Action(battle, isPlayer) {
	setActionType(FIGHT);
	mMove = move;
	setActionNum(getBattleRef().getLastAction()->getActionNum() + 1);
	if (isPlayer) {
		mAttacker = getBattleRef().getPlayerPokemon();
		mDefender = getBattleRef().getOpponentPokemon();
	}
	else {
		mAttacker = getBattleRef().getOpponentPokemon();
		mDefender = getBattleRef().getPlayerPokemon();
	}
}

Pokemon* Fight::getAttacker() {
	return mAttacker;
}

Pokemon* Fight::getDefender() {
	return mDefender;
}

Move* Fight::getMove() {
	return mMove;
}

int Fight::getPriority() {
	return mMove->getPriority();
}

// false if no move selected
bool Fight::selectMove() {
	vector<Move*> moves = mAttacker->getMoves();
	vector<int> pps = mAttacker->getMovesPP();

	for (int i = 0; i < moves.size(); i++) {
		cout << i + 1 << ": ";
		moves[i]->print();
		cout << "   Current PP: " << pps[i] << " / " << moves[i]->getBasePP() << endl;
	}
	cout << "Press 0 to return to previous menu." << endl;

	int choice = selectOption(1, moves.size(), true);
	if (choice == 0) {
		return false;
	}
	while (pps[choice - 1] < 1) {
		cout << "Move is out of PP!" << endl;
		choice = selectOption(1, moves.size(), true);
		if (choice == 0) {
			return false;
		}
	}
	mMoveSlot = choice - 1;
	mMove = moves[mMoveSlot];

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
	int critTable[5] = { 3, 6, 12, 16, 24 };
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

bool Fight::dealsDirectDamage() {
	vector<string> moveList = { "Bide", "Counter", "Dragon Rage", "Mirror Coat", "Night Shade", "Psywave", "Seismic Toss", "Sonic Boom", "Super Fang" };
	if (find(moveList.begin(), moveList.end(), mMove->getMoveName()) != moveList.end()) {
		return true;
	}
	return false;
}

int Fight::calcDirectDamage() {
	string moveName = mMove->getMoveName();
	if (moveName == "Sonic Boom") {
		return 20;
	}
	if (moveName == "Dragon Rage") {
		return 40;
	}
	if (moveName == "Night Shade" || moveName == "Seismic Toss") {
		return mAttacker->getLevel();
	}
	if (moveName == "Super Fang") {
		return floor(mDefender->getCurrentHP() / 2);
	}
	if (moveName == "Psywave") {
		return (rand() % (int)round(mAttacker->getLevel() * 1.5)) + 1;
	}
	if (moveName == "Counter" || moveName == "Mirror Coat") {
		Action* lastAction = getBattleRef().getLastAction();
		if (lastAction->getActionType() == FIGHT) {
			Fight* lastFight = dynamic_cast<Fight*>(lastAction);
			if (lastFight->getDefender() != mAttacker) {
				return 0;
			}
			if (moveName == "Counter" && lastFight->getMove()->getCategory() != PHYSICAL) {
				return 0;
			}
			if (moveName == "Mirror Move" && lastFight->getMove()->getCategory() != SPECIAL) {
				return 0;
			}
			return lastFight->getParameter() * 2;
		}
		//cout << "Not a fight action" << endl;
		return 0;
	}
	return 0;


}

void Fight::doDamage(int damage) {
	if (damage > mDefender->getCurrentHP()) {
		damage = mDefender->getCurrentHP();
	}

	setParameter(damage); // storing amount of damage done
	mDefender->takeDamage(damage);
}

void Fight::makeAttack() {
	cout << mAttacker->getNickname() << " used " << mMove->getMoveName() << "!" << endl;

	mAttacker->decMovePP((MoveNum)mMoveSlot);

	setParameter(0);

	double hitChance = calcAccuracy(mMove->getBaseAccuracy());
	int hitVal = rand() % 100;
	if (hitChance < hitVal) {
		cout << "But it missed!" << endl;
		return;
	}

	if (mMove->getCategory() != STATUS) {
		int damage;
		if (dealsDirectDamage()) {
			damage = calcDirectDamage();
		}
		else {
			double damageMultiplier = calcEffectiveness(mMove->getType());
			if (damageMultiplier == 0) {
				cout << "It had no effect..." << endl;
				return;
			}
			else if (damageMultiplier > 1) {
				cout << "It's super effective!" << endl;
			}
			else if (damageMultiplier < 1) {
				cout << "It's not very effective..." << endl;
			}
			//cout << "DAMAGE MULTIPLIER: " << damageMultiplier << endl;

			double critMultiplier = calcCrit(mMove->getCritRate());

			if (critMultiplier > 1) {
				cout << "A critical hit!" << endl;
			}

			damage = round(calcDamage(critMultiplier) * damageMultiplier);
		}

		doDamage(damage);
		cout << "The attack did " << damage << " damage!" << endl;
	}
	//TODO status stuff

}

void Fight::execute() {
	mDefender = getBattleRef().getPokemon(!isPlayerAction());
	makeAttack();
}

void Fight::printPreview() {
	cout << "-------------------------" << endl;
	cout << "Fight Action" << endl;
	cout << "Attacking Pokemon: " << endl;
	cout << " ";
	mAttacker->printLight();
	//cout << "  " << mAttacker->getNickname() << " (" << mAttacker->getSpecies()->getSpecies() << ")" << endl;
	cout << "Move to use: " << mMove->getMoveName() << endl;
	cout << "-------------------------" << endl;
}

void Fight::print() {
	cout << "-------------------------" << endl;
	cout << "Fight Action" << endl;
	cout << "Attacking Pokemon: " << endl;
	cout << " ";
	mAttacker->printLight();
	cout << "Defending Pokemon: " << endl;
	cout << " ";
	mDefender->printLight();
	cout << "Move Used: " << mMove->getMoveName() << endl;
	cout << "Damage Done: " << getParameter() << endl;
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
	mTrainer = getBattleRef().getTrainer(isPlayer);
	mSwitchedOut = getBattleRef().getPokemon(isPlayer);
	setActionNum(getBattleRef().getLastAction()->getActionNum() + 1);
}

// false if no Pokemon selected
bool Switch::selectPokemon() {
	vector<Pokemon*> party = mTrainer->getParty();
	for (int i = 0; i < party.size(); i++) {
		cout << i + 1 << ": ";
		party[i]->print();
	}
	bool back = false;
	if (getParameter() == 0) {
		cout << "Press 0 to return to previous menu." << endl;
		back = true;
	}
	int choice = selectOption(1, party.size(), back);
	if (choice == 0) {
		return false;
	}
	while (true) {
		if (party[choice - 1]->getCurrentHP() < 1) {
			cout << "It has no energy to fight!" << endl;
		}
		else if (party[choice - 1] == mSwitchedOut) {
			cout << "Select a different Pokemon." << endl;
		}
		else {
			break;
		}
		choice = selectOption(1, party.size(), back);
		if (choice == 0) {
			return false;
		}
	}

	getBattleRef().resetStatChanges(isPlayerAction());
	mSwitchedIn = party[choice - 1];
	return true;
}

void Switch::switchPokemon() {
	if (getParameter() == 0) {
		cout << "Withdrew " << mSwitchedOut->getNickname() << "!" << endl;
	}
	cout << "Send out " << mSwitchedIn->getNickname() << "!" << endl;
	getBattleRef().setPokemon(isPlayerAction(), mSwitchedIn);
}

void Switch::execute() {
	switchPokemon();
}

void Switch::print() {
	cout << "-------------------------" << endl;
	cout << "Switch Action" << endl;
	cout << "Switching Out Pokemon: " << endl;
	cout << " ";
	mSwitchedOut->printLight();
	cout << "Switching In Pokemon: " << endl;
	cout << " ";
	mSwitchedIn->printLight();
	cout << "-------------------------" << endl;
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
	setActionNum(getBattleRef().getLastAction()->getActionNum() + 1);
}

//bool Flee::wasSuccessful() {
//	return mSuccess;
//}

int Flee::attemptEscape() {
	int fleeSpd = getBattleRef().getPokemon(isPlayerAction())->getStat(SPD);
	int chaseSpd = getBattleRef().getPokemon(!isPlayerAction())->getStat(SPD);

	if (fleeSpd >= chaseSpd) {
		//cout << "Got away safely!" << endl;
		return 1;
	}

	int escapeOdds = (((fleeSpd * 128) / chaseSpd) + 30 * getBattleRef().getEscapeAttempts()) % 256;
	int escapeVal = rand() % 256;

	if (escapeOdds > escapeVal) {
		//cout << "Got away safely!" << endl;
		return 1;
	}

	getBattleRef().incEscapeAttempts();
	cout << "Couldn't get away!" << endl;
	return -1;
}

void Flee::execute() {
	setParameter(attemptEscape());
}

void Flee::print() {
	cout << "-------------------------" << endl;
	cout << "Flee Action" << endl;
	if (getParameter() > 0) {
		cout << "   Success" << endl;
	}
	else {
		cout << "   Failure" << endl;
	}
	cout << "-------------------------" << endl;
}
