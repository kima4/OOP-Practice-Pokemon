#ifndef BATTLEOVERVIEW_H
#define BATTLEOVERVIEW_H

#include <string>
#include <vector>

#include "../TrainerInfo/Trainer.h"

enum ActionType { FIGHT, BAG, SWITCH, FLEE };

class Action {
public:
	Action(bool isPlayer);
	ActionType getActionType();
	void setActionType(ActionType actionType);


private:
	ActionType mActionType;
	bool mIsPlayer;



};

class Fight : public Action {
public:
	Fight(bool isPlayer, Move* move);
	int getPriority();

private:
	//int mPriority;
	Move* mMove;

};

class Bag : public Action {
public:
	//Bag();

private:
	//Item mItem;

};

class Switch : public Action {
public:
	Switch(bool isPlayer, Pokemon* switchIn);

private:


};

class Flee : public Action {
public:
	Flee(bool isPlayer);

private:


};


class BattleOverview {
public:
	BattleOverview(Trainer* player, Pokemon* wild);
	BattleOverview(Trainer* player, Trainer* opponent);

	void battle();
	bool battleStep(Action* action1, Action* action2);
	Action* selectAction(bool isPlayer);
	bool attackOrder(Action* playerAction, Action* opponentAction);
	bool checkSpeeds();
	bool determineOrder(Action* playerAction, Action* opponentAction);
	bool performAction(Action* action);

	bool isFinished();

private:
	vector<Trainer*> mTrainers;

	Pokemon* mPlayerPokemon;
	Pokemon* mOpponentPokemon;

	//Battle mBattle;
	vector<Action*> mActionHistory;
	int mTurnNum;

};





/*class Battle {
public:
	Battle(Trainer* player, Trainer* opponent);
	Battle(Trainer* player, Pokemon* wild);

	/**
	 * Battle menu options 
	 * /

	// fight
	Move** getMoves();
	bool checkAttackUsability(int moveSlot);
	double getStatChangeVal(bool isNormalStat, int statChange);
	double getAccuracy(Move* move);
	double calcAtkToDef(Category category, double crit);
	double stabBonus(Type moveType);
	double calcDamage(Move* move, double crit);
	double calcEffectiveness(Type moveType);
	double critBonus(int critRatio);
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



	Pokemon* mPlayerPokemon;
	Pokemon* mOpponentPokemon;

	Pokemon* mAttackingPokemon;
	Pokemon* mDefendingPokemon;

	int mEscapeAttempts;

};*/




#endif
