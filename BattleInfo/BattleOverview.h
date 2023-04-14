#ifndef BATTLEOVERVIEW_H
#define BATTLEOVERVIEW_H

#include <string>
#include <vector>
#include <stack>

#include "../TrainerInfo/Trainer.h"

enum ActionType { FIGHT, BAG, SWITCH, FLEE, MISTAKE };

class Action;
class Fight;
class Bag;
class Switch;
class Flee;



class BattleOverview {
public:
	BattleOverview();
	BattleOverview(Trainer* player, Pokemon* wild);
	BattleOverview(Trainer* player, Trainer* opponent);

	//void startBattle(Pokemon* pPokemon, Pokemon* oPokemon);
	void battle();
	void battleStep(Action* action1, Action* action2);
	Action* selectAction(bool isPlayer);
	int selectOption(int min, int max);
	Action* createAction(bool isPlayer, int choice);
	Action* getLastAction();

	bool attackOrder(Fight* playerAction, Fight* opponentAction);
	bool checkSpeeds();
	bool determineOrder(Action* playerAction, Action* opponentAction);
	void performAction(Action* action);
	
	Trainer* getTrainer(bool isPlayer);
	Pokemon* getPlayerPokemon();
	Pokemon* getOpponentPokemon();

	int getStatChange(bool isPlayer, Stat stat);
	void setStatChange(bool isPlayer, Stat stat, int statChange);
	void addStatChanges(bool isPlayer, int* statChanges);
	void resetStatChanges(bool isPlayer);


	bool isWild();
	
	int getTurnNum();
	
	int getEscapeAttempts();
	void incEscapeAttempts();

	bool isFinished();

private:
	vector<Trainer*> mTrainers;

	//Battle* mBattle;
	Pokemon* mPlayerPokemon;
	Pokemon* mOpponentPokemon;

	int mPStatChanges[NUM_STAT_CHANGES];
	int mOStatChanges[NUM_STAT_CHANGES];

	bool mIsWild;

	stack<Action*> mToDo;
	vector<Action*> mActionHistory;
	int mTurnNum;

	int mEscapeAttempts;

};

class Action {
public:
	Action(BattleOverview& battle, bool isPlayer);
	ActionType getActionType();
	void setActionType(ActionType actionType);
	virtual void execute();
	bool isPlayerAction();
	BattleOverview& getBattleRef();

	void setParameter(int val);
	int getParameter();

	virtual void print();

private:
	int mParameter;

	ActionType mActionType;
	bool mIsPlayer;
	BattleOverview& mBattle;



};

class Fight : public virtual Action {
public:
	Fight(BattleOverview& battle, bool isPlayer);
	Fight(BattleOverview& battle, bool isPlayer, Move* move);
	int getPriority();

	
	bool selectMove();

	int getAttackerStatChange(Stat stat);
	int getDefenderStatChange(Stat stat);

	double calcStatChangeMult(Stat stat, int statChange);

	double calcAccuracy(int acc);
	double calcEffectiveness(Type moveType);
	double calcCrit(int critRatio);
	double calcAtkToDef(double crit);
	double calcSTAB(Type moveType);
	double calcDamage(double crit);
	
	void doDamage(int damage);
	void makeAttack();

	void execute();

	void print();

private:
	//int mPriority;
	Move* mMove;
	Pokemon* mAttacker;
	Pokemon* mDefender;

};

class Bag : public virtual Action {
public:
	//Bag();

private:
	//Item mItem;

};

class Switch : public virtual Action {
public:
	Switch(BattleOverview& battle, bool isPlayer);

private:


};

class Flee : public virtual Action {
public:
	Flee(BattleOverview& battle, bool isPlayer);
	//bool wasSuccessful();

	int attemptEscape();
	void execute();

private:
	//bool mSuccess;

};



#endif
