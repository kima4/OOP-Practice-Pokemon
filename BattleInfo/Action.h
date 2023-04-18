#ifndef ACTION_H
#define ACTION_H

#include "BattleOverview.h"

class BattleOverview;

enum ActionType { FIGHT, BAG, SWITCH, FLEE, MISTAKE };


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

	int getTurnNum();
	int getActionNum();
	void setActionNum(int actionNum);

	int selectOption(int min, int max, bool back);

	virtual void printPreview();
	virtual void print();

private:
	/*
	 * Fight - damage done
	 *
	 * Switch - 0 = normal switch, 1 = emergency switch
	 * Flee - -1 = failure, 1 = success
	 */
	int mParameter;

	int mTurnNum;
	int mActionNum;

	ActionType mActionType;
	bool mIsPlayer;
	BattleOverview& mBattle;



};

class Fight : public virtual Action {
public:
	Fight(BattleOverview& battle, bool isPlayer);
	Fight(BattleOverview& battle, bool isPlayer, Move* move);

	Pokemon* getAttacker();
	Pokemon* getDefender();
	Move* getMove();

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

	bool dealsDirectDamage();
	int calcDirectDamage();

	void doDamage(int damage);
	void makeAttack();

	void execute();

	void printPreview();
	void print();

private:
	int mMoveSlot;
	Move* mMove;
	Pokemon* mAttacker;
	Pokemon* mDefender;

};

class BattleBag : public virtual Action {
public:
	//Bag();

private:
	//Item mItem;

};

class Switch : public virtual Action {
public:
	Switch(BattleOverview& battle, bool isPlayer);

	bool selectPokemon();
	void switchPokemon();
	void execute();

	void print();

private:
	Trainer* mTrainer;
	Pokemon* mSwitchedOut;
	Pokemon* mSwitchedIn;

};

class Flee : public virtual Action {
public:
	Flee(BattleOverview& battle, bool isPlayer);
	//bool wasSuccessful();

	int attemptEscape();
	void execute();

	void print();

private:
	//bool mSuccess;

};


#endif