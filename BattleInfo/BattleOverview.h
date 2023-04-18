#ifndef BATTLEOVERVIEW_H
#define BATTLEOVERVIEW_H

#include <string>
#include <vector>
#include <stack>

#include "../TrainerInfo/Trainer.h"
#include "Action.h"

class Action;
class Fight;
class BattleBag;
class Switch;
class Flee;



class BattleOverview {
public:
	BattleOverview();
	BattleOverview(Trainer* player, Pokemon* wild);
	BattleOverview(Trainer* player, Trainer* opponent);

	//void startBattle(Pokemon* pPokemon, Pokemon* oPokemon);
	void battle();
	void performTurn(Action* action1, Action* action2);

	int selectOption(int min, int max);
	Action* createAction(bool isPlayer, int choice);
	Action* selectAction(bool isPlayer);
	Action* getLastAction();
	void deleteAction(Action*);
	void deleteActionChain();

	bool attackOrder(Fight* playerAction, Fight* opponentAction);
	bool checkSpeeds();
	bool determineOrder(Action* playerAction, Action* opponentAction);
	void performAction(Action* action);
	bool emergencySwitch(bool isPlayer);
	
	Trainer* getTrainer(bool isPlayer);
	Pokemon* getPokemon(bool isPlayer);
	Pokemon* getPlayerPokemon();
	Pokemon* getOpponentPokemon();
	void setPokemon(bool isPlayer, Pokemon* pokemon);

	int getStatChange(bool isPlayer, Stat stat);
	void setStatChange(bool isPlayer, Stat stat, int statChange);
	void addStatChanges(bool isPlayer, int* statChanges);
	void resetStatChanges(bool isPlayer);


	bool isWild();
	
	int getTurnNum();
	
	int getEscapeAttempts();
	void incEscapeAttempts();

	bool isFinished();

	void printActionChain();

private:
	vector<Trainer*> mTrainers;

	//Battle* mBattle;
	Pokemon* mPlayerPokemon;
	Pokemon* mOpponentPokemon;

	int mPStatChanges[NUM_STAT_CHANGES];
	int mOStatChanges[NUM_STAT_CHANGES];

	bool mIsWild;

	vector<Action*> mToDo;
	vector<Action*> mActionHistory;
	int mTurnNum;

	int mEscapeAttempts;

};




#endif
