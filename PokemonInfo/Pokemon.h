#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <tuple>
#include <map>

#include "PokemonSpecies.h"
#include "../MoveInfo/Move.h"

using namespace std;

enum MoveNum { MOVE_1, MOVE_2, MOVE_3, MOVE_4, NUM_MOVES };

class Pokemon {
public:

	//constructors
	Pokemon(string species, int level);
	//Pokemon(string species, int level, string nickname);

	void initIVs();
	void initEVs();
	void initStats();
	void initMoves();

	void setSpecies(string species);
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
	void takeDamage(int damage);
	void restoreHP(int healing);
	void fullyHeal();
	bool isFainted();

	// moves
	Move* getMove(MoveNum moveSlot);
	string getMoveName(MoveNum moveSlot);
	vector<Move*> getMoves();
	//Move** getMoves();
	vector<string> getMoveNames();
	void setMove(string moveName, MoveNum moveSlot);
	void setMove(Move* move, MoveNum moveSlot);
	void setMoves(string moveNames[NUM_MOVES]);
	void setMoves(Move* moves[NUM_MOVES]);
	void setMoves(vector<string> moves);

	void refillMove(MoveNum moveSlot);
	void refillMoves();
	int getMovePP(MoveNum moveSlot);
	vector<int> getMovesPP();
	void setMovePP(int pp, MoveNum moveSlot);
	void decMovePP(MoveNum moveSlot);
	bool alreadyKnows(string moveName);
	void learnMove(string moveName, MoveNum moveSlot);

	void print();
	void printVerbose();

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

	// moves
	Move* mMoves[NUM_MOVES];
	int mMovePP[NUM_MOVES];

};




#endif
