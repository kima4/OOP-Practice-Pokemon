#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <tuple>
#include <map>

#include "PokemonSpecies.h"
#include "../MoveInfo/Move.h"

using namespace std;

class Pokemon {
public:

	//constructors
	Pokemon(string species, int level);
	//Pokemon(string species, int level, string nickname);

	void initIVs();
	void initEVs();
	void initStats();
	void initMoves();

	PokemonSpecies* getSpecies();

	int getLevel();
	void setLevel(int level);

	string getNickname();
	void setNickname(string nickname);

	Gender getGender();
	void setGender();
	void setGender(Gender gender);

	// iv getters
	int getIVHP();
	int getIVAtk();
	int getIVDef();
	int getIVSpAtk();
	int getIVSpDef();
	int getIVSpd();
	int* getIVs();

	// ev getters
	int getEVHP();
	int getEVAtk();
	int getEVDef();
	int getEVSpAtk();
	int getEVSpDef();
	int getEVSpd();
	int* getEVs();
	
	// ev setters
	void setEVHP(int ev);
	void setEVAtk(int ev);
	void setEVDef(int ev);
	void setEVSpAtk(int ev);
	void setEVSpDef(int ev);
	void setEVSpd(int ev);
	void setEVs(int* evs);
	void addEVs(int* evs);

	// stats
	int calcMaxHP();
	int calcOtherStat(Stat stat);

	int getStat(Stat stat);

	int getCurrentHP();
	void setCurrentHP(int hp);

	int getStatChange(Stat stat);
	void setStatChange(Stat stat, int change);
	void addStatChange(Stat stat, int change);
	void resetStatChanges();

	// moves
	Move* getMove(int moveSlot);
	Move** getMoves();
	void setMove(Move* move, int moveSlot);
	void setMoves(Move* moves[4]);
	void refillMove(int moveSlot);
	void refillMoves();
	int getMovePP(int moveSlot);
	void setMovePP(int pp, int moveSlot);
	void decMovePP(int moveSlot);

	void print();

private:
	PokemonSpecies* mSpecies;
	unsigned int mLevel;
	string mNickname;
	Gender mGender;

	// ivs
	int mIVs[NUM_STATS];

	// evs
	int mEVs[NUM_STATS];

	// stats
	int mStats[NUM_STATS];
	int mCurrentHP;
	int mStatChanges[NUM_STAT_CHANGES];

	// moves
	Move* mMoves[4];
	int mMovePP[4];

};




#endif
