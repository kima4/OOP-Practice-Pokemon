#include <iostream>
#include <string>
#include <tuple>

#include "../MiscInfo/Types.h"
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
	mBaseStats[HP] = get<0>(stats);
	mBaseStats[ATK] = get<1>(stats);
	mBaseStats[DEF] = get<2>(stats);
	mBaseStats[SPATK] = get<3>(stats);
	mBaseStats[SPDEF] = get<4>(stats);
	mBaseStats[SPD] = get<5>(stats);
}

void PokemonSpecies::initBreeding(string species) {
	tuple<int, EggGroup, EggGroup, int> breeding = SpeciesBreeding.at(species);
	mGenderRatio = get<0>(breeding);
	mEggGroups[0] = get<1>(breeding);
	mEggGroups[1] = get<2>(breeding);
	mEggCycles = get<3>(breeding);
}

void PokemonSpecies::print() {
	cout << mSpecies << '\n';

	cout << getTypeString(mTypes[0]) << "  " << getTypeString(mTypes[1]) << '\n';

	cout << "--------- Base Stats ---------\n";
	cout << "     HP: " << mBaseStats[HP] << '\n';
	cout << "    Atk: " << mBaseStats[ATK] << '\n';
	cout << "    Def: " << mBaseStats[DEF] << '\n';
	cout << "  SpAtk: " << mBaseStats[SPATK] << '\n';
	cout << "  SpDef: " << mBaseStats[SPDEF] << '\n';
	cout << "    Spd: " << mBaseStats[SPD] << '\n';

}

string PokemonSpecies::getSpecies() {
	return mSpecies;
}

Type* PokemonSpecies::getTypes() {
	return { mTypes };
}

int PokemonSpecies::getBaseHP() {
	return mBaseStats[HP];
}
int PokemonSpecies::getBaseAtk() {
	return mBaseStats[ATK];
}
int PokemonSpecies::getBaseDef() {
	return mBaseStats[DEF];
}
int PokemonSpecies::getBaseSpAtk() {
	return mBaseStats[SPATK];
}
int PokemonSpecies::getBaseSpDef() {
	return mBaseStats[SPDEF];
}
int PokemonSpecies::getBaseSpd() {
	return mBaseStats[SPD];
}
int* PokemonSpecies::getBaseStats() {
	return mBaseStats;
}

int PokemonSpecies::getGenderRatio() {
	return mGenderRatio;
}

void PokemonSpecies::setType1(Type type) {
	mTypes[0] = type;
}

void PokemonSpecies::setType2(Type type) {
	mTypes[1] = type;
}