#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <tuple>
#include <map>

#include "PokemonSpecies.h"
#include "../MoveInfo/Move.h"

using namespace std;

class Pokemon : protected PokemonSpecies {
public:

	//constructors
	Pokemon(string species, int level);
	Pokemon(string species, int level, string nickname);

	void initIVs();
	void initEVs();
	void initStats();

	int getLevel();
	void setLevel(int level);

	string getNickname();
	void setNickname(string nickname);

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
	int calcOtherStat(int stat);

	int getStat(int stat);

	int getCurrentHP();
	void setCurrentHP(int hp);

	void print();

private:
	unsigned int mLevel;
	string mNickname;

	// ivs
	int mIVs[NUM_STATS];

	// evs
	int mEVs[NUM_STATS];

	// stats
	int mStats[NUM_STATS];
	int mCurrentHP;

	Move* mMove1;
	Move* mMove2;
	Move* mMove3;
	Move* mMove4;

	int mMove1PP;
	int mMove2PP;
	int mMove3PP;
	int mMove4PP;

};




#endif
