#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <algorithm>

#include "BattleOverview.h"
#include "BattleFunctions.h"


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

// battle loop
void BattleOverview::battle() {
	// to prevent undefined behavior
	Action* action0 = new Action(*this, true);
	mActionHistory.push_back(action0);

	while (!isFinished()) {
		emergencySwitch(true);
		emergencySwitch(false);
		mTurnNum++;
		cout << "\nPlayer Action:" << endl;
		Action* playerAction = selectAction(true);
		while (playerAction->getActionType() == MISTAKE) {
			delete playerAction;
			playerAction = selectAction(true);
		}
		cout << "\nOpponent Action:" << endl;
		Action* opponentAction = selectAction(false);
		while (opponentAction->getActionType() == MISTAKE) {
			delete opponentAction;

			opponentAction = selectAction(false);
		}

		if (determineOrder(playerAction, opponentAction)) {
			
			performTurn(playerAction, opponentAction);
		}
		else {
			performTurn(opponentAction, playerAction);
		}
	}
	printActionChain();
	deleteActionChain();
}

void BattleOverview::performTurn(Action* action1, Action* action2) {
	performAction(action1);
	mActionHistory.push_back(action1);
	if (isFinished()) {
		return;
	}
	if (emergencySwitch(true) || emergencySwitch(false)) {
		
		//action2->printPreview();
		deleteAction(action2);
		return;
	}
	performAction(action2);
	mActionHistory.push_back(action2);
	return;
}

int BattleOverview::selectOption(int min, int max) {
	int choice;
	cout << "Select an option: ";
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
			action->printPreview();
			return action;
		}
		delete action;
		break;
	}
	case 2:
		//return new Bag();
	case 3:
	{
		Switch* action = new Switch(*this, isPlayer);
		action->setParameter(0);
		if (action->selectPokemon()) {
			action->print();
			return action;
		}
		delete action;
		break;
	}
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

Action* BattleOverview::selectAction(bool isPlayer) {
	cout << "1. Fight" << endl;
	cout << "2. Bag" << endl;
	cout << "3. Switch" << endl;
	cout << "4. Flee" << endl;

	int choice = selectOption(1, 4);

	return createAction(isPlayer, choice);
}

Action* BattleOverview::getLastAction() {
	return mActionHistory.back();
}

void BattleOverview::deleteAction(Action* action) {
	ActionType actType = action->getActionType();
	switch (actType) {
	case FIGHT:
	{
		Fight* f = dynamic_cast<Fight*>(action);
		delete f;
		break;
	}
	case BAG:
	{
		//BattleBag* b = dynamic_cast<BattleBag*>(action);
		//delete b;
		break;
	}
	case SWITCH:
	{
		Switch* s = dynamic_cast<Switch*>(action);
		delete s;
		break;
	}
	case FLEE:
	{
		Flee* f = dynamic_cast<Flee*>(action);
		delete f;
		break;
	}
	default:
		delete action;
	}
}

void BattleOverview::deleteActionChain() {
	for (int i = 0; i < mActionHistory.size(); i++) {
		deleteAction(mActionHistory[i]);
	}
}

// true if player goes first
bool BattleOverview::attackOrder(Fight* playerAction, Fight* opponentAction) {
	int playerPriority = playerAction->getPriority();
	int opponentPriority = opponentAction->getPriority();
	cout << "Player Priority: " << playerPriority << endl;
	cout << "Opponent Priority: " << opponentPriority << endl;
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

// true if emergency switch occurs
bool BattleOverview::emergencySwitch(bool isPlayer) {

	if (getPokemon(isPlayer)->isFainted()) {
		cout << "\nChoose a Pokemon to send out:" << endl;

		Switch* eSwitch = new Switch(*this, isPlayer);
		eSwitch->setParameter(1);
		eSwitch->selectPokemon();
		performAction(eSwitch);
		mActionHistory.push_back(eSwitch);
		return true;
	}
	return false;
}

Trainer* BattleOverview::getTrainer(bool isPlayer) {
	if (isPlayer) {
		return mTrainers[0];
	}
	return mTrainers[1];
}

Pokemon* BattleOverview::getPokemon(bool isPlayer) {
	if (isPlayer) {
		return getPlayerPokemon();
	}
	return getOpponentPokemon();
}

Pokemon* BattleOverview::getPlayerPokemon() {
	return mPlayerPokemon;
}

Pokemon* BattleOverview::getOpponentPokemon() {
	return mOpponentPokemon;
}

void BattleOverview::setPokemon(bool isPlayer, Pokemon* pokemon) {
	if (isPlayer) {
		mPlayerPokemon = pokemon;
	}
	else {
		mOpponentPokemon = pokemon;
	}
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
			cout << "Trainer " << i << " ran out of Pokemon!" << endl;
			return true;
		}
	}

	// check if wild pokemon if fainted ******TODO add captured
	if (mIsWild && mOpponentPokemon->isFainted()) {
		cout << "The wild Pokemon fainted!" << endl;
		return true;
	}

	// check if someone fled successfully
	if (mActionHistory.size() > 0) {
		Action* lastAction = getLastAction();
		if (lastAction->getActionType() == FLEE) {
			if (lastAction->getParameter() > 0) {
				cout << "Got away safely!" << endl;
				return true;
			}
		}
	}

	return false;
}

void BattleOverview::printActionChain() {
	for (int i = 1; i < mActionHistory.size(); i++) {
		mActionHistory[i]->print();
	}
}





