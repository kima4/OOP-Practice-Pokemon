#include <iostream>
#include <string>
#include <tuple>

#include "../MiscInfo/Types.h"
#include "PokemonSpecies.h"
#include "PokemonDatabase.h"
#include "PokemonMoveList.h"

using namespace std;

/**
 * Create a PokemonSpecies object
 *
 * @param species - the species name
 * @return - a new PokemonSpecies object
 */
PokemonSpecies::PokemonSpecies(string species) : mSpecies(species) {
	initTypes(species);
	initStats(species);
	initBreeding(species);
	initMoves(species);
}

/**
 * Set the typing of the specified pokemon
 *
 * @param species - the species name
 * @return - none, but the PokemonSpecies object has filled in types
 */
void PokemonSpecies::initTypes(string species) {
	tuple<Type, Type> types = SpeciesTypes.at(species);
	mTypes[0] = get<0>(types);
	mTypes[1] = get<1>(types);
}

/**
 * Set the base stats of the specified pokemon
 *
 * @param species - the species name
 * @return - none, but the PokemonSpecies object has filled in base stats
 */
void PokemonSpecies::initStats(string species) {
	tuple<int, int, int, int, int, int> stats = SpeciesStats.at(species);
	mBaseStats[HP] = get<0>(stats);
	mBaseStats[ATK] = get<1>(stats);
	mBaseStats[DEF] = get<2>(stats);
	mBaseStats[SPATK] = get<3>(stats);
	mBaseStats[SPDEF] = get<4>(stats);
	mBaseStats[SPD] = get<5>(stats);
}

/**
 * Set the breeding information of the specified pokemon
 *
 * @param species - the species name
 * @return - none, but the PokemonSpecies object has filled in breeding information
 */
void PokemonSpecies::initBreeding(string species) {
	tuple<int, EggGroup, EggGroup, int> breeding = SpeciesBreeding.at(species);
	mGenderRatio = get<0>(breeding);
	mEggGroups[0] = get<1>(breeding);
	mEggGroups[1] = get<2>(breeding);
	mEggCycles = get<3>(breeding);
}

/**
 * Set the move information information of the specified pokemon
 *
 * @param species - the species name
 * @return - none, but the PokemonSpecies object has filled in move information
 */
void PokemonSpecies::initMoves(string species) {
	mLearnset = PokemonLearnset.at(species);
}

/**
 * Print information about the PokemonSpecies object to console
 */
void PokemonSpecies::print() {
	cout << mSpecies << endl;

	cout << "   " << getTypeString(mTypes[0]) << "  " << getTypeString(mTypes[1]) << endl;
}


void PokemonSpecies::printVerbose() {
	print();

	cout << "   --------- Base Stats ---------" << endl;
	cout << "        HP: " << mBaseStats[HP] << endl;
	cout << "       Atk: " << mBaseStats[ATK] << endl;
	cout << "       Def: " << mBaseStats[DEF] << endl;
	cout << "     SpAtk: " << mBaseStats[SPATK] << endl;
	cout << "     SpDef: " << mBaseStats[SPDEF] << endl;
	cout << "       Spd: " << mBaseStats[SPD] << endl;

}

/**
 * Basic information getters
 */
string PokemonSpecies::getSpecies() {
	return mSpecies;
}

Type* PokemonSpecies::getTypes() {
	return { mTypes };
}

int PokemonSpecies::getGenderRatio() {
	return mGenderRatio;
}

/**
 * Base stat getters
 */
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

/**
 * Move learnset information getters
 */
vector<string> PokemonSpecies::getMovesAt(int level) {
	vector<string> learnedMoves;
	for (auto const& p : mLearnset) {
		if (p.first == level) {
			learnedMoves.push_back(p.second);
		}
	}
	return learnedMoves;
}
