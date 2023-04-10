#ifndef POKEMONSPECIES_H
#define POKEMONSPECIES_H

#include <string>
#include <tuple>
#include <map>

#include "../TypeInfo/Types.h"

using namespace std;

// class for all species
class PokemonSpecies {
public:

	// constructor
	PokemonSpecies(string species);
	void initTypes(string species);
	void initStats(string species);


	/*
	// constructor
	PokemonSpecies(
		int dexNum,
		string species,
		Type type1, Type type2,
		int baseHP, int baseAtk, int baseDef, int baseSpAtk, int baseSpDef, int baseSpd,
		int genderRatio
	);*/

	// prints species information
	void print();

	// gets species name
	string getSpecies();

	// gets species types
	tuple<Type, Type> getTypes();
	void setType1(Type type);
	void setType2(Type type);

	// gets base stats
	int getBaseHP();
	int getBaseAtk();
	int getBaseDef();
	int getBaseSpAtk();
	int getBaseSpDef();
	int getBaseSpd();
	int* getBaseStats();

	// gets gender ratio
	int getGenderRatio();


protected:
	unsigned int mDexNum;
	string mSpecies;
	Type mType1;
	Type mType2;

	int mBaseStats[6];

	int mGenderRatio;
};






#endif
