#include <iostream>
#include <string>
#include <tuple>

#include "../TypeInfo/Types.h"
#include "PokemonSpecies.h"
#include "PokemonDatabase.h"

using namespace std;

PokemonSpecies::PokemonSpecies(string species) : mSpecies(species) {
	initTypes(species);
	initStats(species);
}

void PokemonSpecies::initTypes(string species) {
	tuple<Type, Type> types = SpeciesTypes.at(species);
	setType1(get<0>(types));
	setType2(get<1>(types));
}

void PokemonSpecies::initStats(string species) {
	tuple<int, int, int, int, int, int> stats = SpeciesStats.at(species);
	mBaseStats[0] = get<0>(stats);
	mBaseStats[1] = get<1>(stats);
	mBaseStats[2] = get<2>(stats);
	mBaseStats[3] = get<3>(stats);
	mBaseStats[4] = get<4>(stats);
	mBaseStats[5] = get<5>(stats);
}

/*
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
}*/

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
	return mBaseStats[0];
}
int PokemonSpecies::getBaseAtk() {
	return mBaseStats[1];
}
int PokemonSpecies::getBaseDef() {
	return mBaseStats[2];
}
int PokemonSpecies::getBaseSpAtk() {
	return mBaseStats[3];
}
int PokemonSpecies::getBaseSpDef() {
	return mBaseStats[4];
}
int PokemonSpecies::getBaseSpd() {
	return mBaseStats[5];
}

int PokemonSpecies::getGenderRatio() {
	return mGenderRatio;
}

void PokemonSpecies::setType1(Type type) {
	mType1 = type;
}

void PokemonSpecies::setType2(Type type) {
	mType2 = type;
}