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



/* ----------------------------------------------------------------
 *
 *
 *
 *                            Action
 *
 *
 *
 * ----------------------------------------------------------------*/

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


/* ----------------------------------------------------------------
 *
 *
 *
 *                            Fight
 *
 *
 *
 * ----------------------------------------------------------------*/

Fight::Fight(bool isPlayer) : Action(isPlayer) {

}

Fight::Fight(bool isPlayer, Move* move) : Action(isPlayer) {
	mMove = move;
}

int Fight::getPriority() {
	return mMove->getPriority();
}

void Fight::execute() {

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

Switch::Switch(bool isPlayer) : Action(isPlayer) {
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

Flee::Flee(bool isPlayer) : Action(isPlayer) {
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

Battle::Battle(Pokemon* pPokemon, Pokemon* oPokemon, bool isWild) : mPlayerPokemon(pPokemon), mOpponentPokemon(oPokemon), mIsWild(isWild) {

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




