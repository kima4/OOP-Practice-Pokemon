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


BattleOverview::BattleOverview(Trainer* player, Pokemon* wild) {
	mTrainers.push_back(player);
	mPlayerPokemon = player->getLead();
	mOpponentPokemon = wild;
	mTurnNum = 0;
	mIsWild = true;
}


BattleOverview::BattleOverview(Trainer* player, Trainer* opponent) {
	mTrainers.push_back(player);
	mTrainers.push_back(opponent);
	mPlayerPokemon = player->getLead();
	mOpponentPokemon = opponent->getLead();
	mTurnNum = 0;
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
	if (isFinished()) {
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
			return action;
		}
		break;
	}
	case 2:
		//return new Bag();
	case 3:
		return new Switch(*this, isPlayer);
	case 4:
		return new Flee(*this, isPlayer);
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
			Flee* fleeAction = dynamic_cast<Flee*>(getLastAction());
			if (fleeAction->wasSuccessful()) {
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
}

Fight::Fight(BattleOverview& battle, bool isPlayer, Move* move) : Action(battle, isPlayer) {
	setActionType(FIGHT);
	mMove = move;
}

int Fight::getPriority() {
	return 0; // TODO implement priority
	//return mMove->getPriority(); 
}

void Fight::execute() {
	//Move* toUse = selectMove();
}

// false if no move selected
bool Fight::selectMove() {
	vector<Move*> moves;
	if (isPlayerAction()) {
		moves = getBattleRef().getPlayerPokemon()->getMoves();
	}
	else {
		moves = getBattleRef().getOpponentPokemon()->getMoves();
	}

	for (int i = 0; i < moves.size(); i++) {
		cout << i + 1 << ":" << endl;
		moves[i]->print();
	}
	cout << "Press 0 to return to previous menu." << endl;

	int choice;
	cin >> choice;
	while (choice < 1 || choice > moves.size()) {
		if (choice == 0) {
			return false;
		}
		cout << "Invalid choice. Choose again: " << endl;
		cin >> choice;
	}

	mMove = moves[choice];

	return true;
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

bool Flee::wasSuccessful() {
	return mSuccess;
}



/* ----------------------------------------------------------------
 *
 *
 *
 *                            Battle
 *
 *
 *
 * ----------------------------------------------------------------*/






