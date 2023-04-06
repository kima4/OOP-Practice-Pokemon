#ifndef POKEMONSPECIES_H
#define POKEMONSPECIES_H

#include <string>
#include <tuple>

#include "../TypeInfo/Types.h"

using namespace std;

// class for all species
class PokemonSpecies {
public:

	// constructor
	PokemonSpecies(
		int dexNum,
		string species,
		Type type1, Type type2,
		int baseHP, int baseAtk, int baseDef, int baseSpAtk, int baseSpDef, int baseSpd,
		int genderRatio
	);

	// prints species information
	void print();

	// gets species name
	string getSpecies();

	// gets species types
	tuple<Type, Type> getTypes();

	// gets base stats
	int getBaseHP();
	int getBaseAtk();
	int getBaseDef();
	int getBaseSpAtk();
	int getBaseSpDef();
	int getBaseSpd();

	// gets gender ratio
	int getGenderRatio();

protected:
	unsigned int mDexNum;
	string mSpecies;
	Type mType1;
	Type mType2;

	unsigned int mBaseHP;
	unsigned int mBaseAtk;
	unsigned int mBaseDef;
	unsigned int mBaseSpAtk;
	unsigned int mBaseSpDef;
	unsigned int mBaseSpd;

	int mGenderRatio;
};






#endif
