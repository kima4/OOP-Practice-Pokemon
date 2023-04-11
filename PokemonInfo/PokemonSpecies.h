#ifndef POKEMONSPECIES_H
#define POKEMONSPECIES_H

#include <string>
#include <tuple>
#include <map>

#include "../MiscInfo/Types.h"
#include "BreedingInfo/Breeding.h"

using namespace std;

enum Stat { HP, ATK, DEF, SPATK, SPDEF, SPD, NUM_STATS};

// class for all species
class PokemonSpecies {
public:

	// constructor
	PokemonSpecies(string species);
	void initTypes(string species);
	void initStats(string species);
	void initBreeding(string species);

	// prints species information
	void print();

	// gets species name
	string getSpecies();

	// gets species types
	Type* getTypes();

	// gets gender ratio
	int getGenderRatio();

	// gets base stats
	int getBaseHP();
	int getBaseAtk();
	int getBaseDef();
	int getBaseSpAtk();
	int getBaseSpDef();
	int getBaseSpd();
	int* getBaseStats();



protected:
	unsigned int mDexNum;
	string mSpecies;
	Type mTypes[2];

	int mBaseStats[NUM_STATS];

	// -1 = genderless, 0 = all male, 1 = 7 male : 1 female, 2 = 3 male : 1 female
	// 4 = 1 male : 1 female, 6 = 1 male : 3 female, 8 = all female
	int mGenderRatio;
	EggGroup mEggGroups[2];
	int mEggCycles;

};






#endif
