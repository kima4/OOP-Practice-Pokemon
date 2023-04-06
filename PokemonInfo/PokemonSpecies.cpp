#include <iostream>
#include <string>
#include <tuple>

#include "../TypeInfo/Types.h"
#include "PokemonSpecies.h"

using namespace std;

PokemonSpecies::PokemonSpecies(
	int dexNum,
	string species,
	Type type1, Type type2,
	int baseHP, int baseAtk, int baseDef, int baseSpAtk, int baseSpDef, int baseSpd,
	int genderRatio
) :
	mDexNum(dexNum),
	mSpecies(species),
	mType1(type1), mType2(type2),
	mBaseHP(baseHP), mBaseAtk(baseAtk), mBaseDef(baseDef), mBaseSpAtk(baseSpAtk), mBaseSpDef(baseSpDef), mBaseSpd(baseSpd),
	mGenderRatio(genderRatio) {

}

void PokemonSpecies::print() {
	cout << mSpecies << '\n';
}

string PokemonSpecies::getSpecies() {
	return mSpecies;
}

tuple<Type, Type> PokemonSpecies::getTypes() {
	return { mType1, mType2 };
}

int PokemonSpecies::getBaseHP() {
	return mBaseHP;
}
int PokemonSpecies::getBaseAtk() {
	return mBaseAtk;
}
int PokemonSpecies::getBaseDef() {
	return mBaseDef;
}
int PokemonSpecies::getBaseSpAtk() {
	return mBaseSpAtk;
}
int PokemonSpecies::getBaseSpDef() {
	return mBaseSpDef;
}
int PokemonSpecies::getBaseSpd() {
	return mBaseSpd;
}

int PokemonSpecies::getGenderRatio() {
	return mGenderRatio;
}

