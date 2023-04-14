#include <iostream>
#include <string>
#include <tuple>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "Pokemon.h"
#include "PokemonList.h"
#include "../MoveInfo/MoveList.h"

/**
 * Create a Pokemon object
 *
 * @param species - the species name
 * @param level - the level
 * @return - a new Pokemon object
 */
Pokemon::Pokemon(string species, int level) {
	setSpecies(species);
	setLevel(level);
	setNickname(species);
	setGender();
	initIVs();
	initEVs();
	initStats();
	setCurrentHP(getStat(HP));
	initMoves();
	refillMoves();
}

/**
 * Set the IVs of the Pokemon object
 *
 * @return - none, but the Pokemon object has randomly generated IVs
 */
void Pokemon::initIVs() {
	for (int i = HP; i != NUM_STATS; i++) {
		mIVs[i] = rand() % 32;
	}
}

/**
 * Set the EVs of the Pokemon object
 *
 * @return - none, but the Pokemon object has EVs of 0 filled in
 */
void Pokemon::initEVs() {
	for (int i = HP; i != NUM_STATS; i++) {
		mEVs[i] = 0;
	}
}

/**
 * Calculate the stat values of the Pokemon object
 *
 * @return - none, but the Pokemon object has filled in stat information
 */
void Pokemon::initStats() {
	mStats[0] = calcMaxHP();
	for (int i = ATK; i != NUM_STATS; i++) {
		mStats[i] = calcOtherStat((Stat)i);
	}
}

/**
 * Sets the moves of the Pokemon object. 
 * Finds the last four moves the Pokemon would learn from leveling up.
 *
 * @return - none, but the Pokemon object has filled in moves
 */
void Pokemon::initMoves() {
	string moves[4] = {"PLACEHOLDER", "PLACEHOLDER", "PLACEHOLDER", "PLACEHOLDER"};

	setMoves(moves); // to prevent segfaults

	int moveSlot = 0;
	vector<string> toLearn;

	for (int i = mLevel; i > 0; i--) {
		vector<string> learnedMoves = mSpecies->getMovesAt(i);
		if (learnedMoves.empty()) {
			continue;
		}

		vector<string> toLearnAtLevel;
		
		for (int j = 0; j < learnedMoves.size(); j++) {
			if (count(toLearn.begin(), toLearn.end(), learnedMoves[j]) == 0) {
				toLearnAtLevel.push_back(learnedMoves[j]);
			}
		}

		random_shuffle(toLearnAtLevel.begin(), toLearnAtLevel.end());

		while (toLearn.size() + toLearnAtLevel.size() > NUM_MOVES) {
			toLearnAtLevel.erase(toLearnAtLevel.end() - 1);
		}
		toLearn.insert(toLearn.end(), toLearnAtLevel.begin(), toLearnAtLevel.end());

		if (toLearn.size() >= 4) {
			break;
		}
	}
	setMoves(toLearn);
}

/**
 * Basic information getters and setters
 */

void Pokemon::setSpecies(string species) {
	try {
		mSpecies = SpeciesList.at(species);
	}
	catch (const out_of_range& e) {
		SpeciesList[species] = new PokemonSpecies(species);
		mSpecies = SpeciesList.at(species);
	}
}

PokemonSpecies* Pokemon::getSpecies() {
	return mSpecies;
}

int Pokemon::getLevel() {
	return mLevel;
}

void Pokemon::setLevel(int level) {
	mLevel = level;
}

string Pokemon::getNickname() {
	return mNickname;
}

void Pokemon::setNickname(string nickname) {
	mNickname = nickname;
}

Gender Pokemon::getGender() {
	return mGender;
}

void Pokemon::setGender() {
	int gr = mSpecies->getGenderRatio();
	if (gr < 0) {
		mGender = UNKNOWN;
	}
	else {
		int gendVal = rand() % 8;
		if (gr <= gendVal) {
			mGender = MALE;
		}
		mGender = FEMALE;
	}
}

void Pokemon::setGender(Gender gender) {
	mGender = gender;
}

/**
 * IV getters
 */
int Pokemon::getIVHP() {
	return mIVs[HP];
}
int Pokemon::getIVAtk() {
	return mIVs[ATK];
}
int Pokemon::getIVDef() {
	return mIVs[DEF];
}
int Pokemon::getIVSpAtk() {
	return mIVs[SPATK];
}
int Pokemon::getIVSpDef() {
	return mIVs[SPDEF];
}
int Pokemon::getIVSpd() {
	return mIVs[SPD];
}
int* Pokemon::getIVs() {
	return mIVs;
}

/**
 * EV getters
 */
int Pokemon::getEVHP() {
	return mEVs[HP];
}
int Pokemon::getEVAtk() {
	return mEVs[ATK];
}
int Pokemon::getEVDef() {
	return mEVs[DEF];
}
int Pokemon::getEVSpAtk() {
	return mEVs[SPATK];
}
int Pokemon::getEVSpDef() {
	return mEVs[SPDEF];
}
int Pokemon::getEVSpd() {
	return mEVs[SPD];
}
int* Pokemon::getEVs() {
	return mEVs;
}

/**
 * EV setters
 */
void Pokemon::setEVHP(int ev) {
	mEVs[HP] = ev;
}
void Pokemon::setEVAtk(int ev) {
	mEVs[ATK] = ev;
}
void Pokemon::setEVDef(int ev) {
	mEVs[DEF] = ev;
}
void Pokemon::setEVSpAtk(int ev) {
	mEVs[SPATK] = ev;
}
void Pokemon::setEVSpDef(int ev) {
	mEVs[SPDEF] = ev;
}
void Pokemon::setEVSpd(int ev) {
	mEVs[SPD] = ev;
}
void Pokemon::setEVs(int* evs) {
	setEVHP(evs[HP]);
	setEVAtk(evs[ATK]);
	setEVDef(evs[DEF]);
	setEVSpAtk(evs[SPATK]);
	setEVSpDef(evs[SPDEF]);
	setEVSpd(evs[SPD]);
}
void Pokemon::addEVs(int* evs) {
	setEVHP(getEVHP() + evs[HP]);
	setEVAtk(getEVAtk() + evs[ATK]);
	setEVDef(getEVDef() + evs[DEF]);
	setEVSpAtk(getEVSpAtk() + evs[SPATK]);
	setEVSpDef(getEVSpDef() + evs[SPDEF]);
	setEVSpd(getEVSpd() + evs[SPD]);
}


/**
 * Stat calculation
 */
int Pokemon::calcMaxHP() {
	int maxHP = mSpecies->getBaseHP() * 2 + getIVHP() + (getEVHP() / 4);
	maxHP *= getLevel();
	maxHP /= 100;
	return maxHP + getLevel() + 10;
}

int Pokemon::calcOtherStat(Stat otherStat) {
	int stat = mSpecies->getBaseStats()[otherStat] * 2 + getIVs()[otherStat] + (getEVs()[otherStat] / 4);
	stat *= getLevel();
	stat /= 100;
	return stat + 5;
}

int Pokemon::getStat(Stat stat) {
	return mStats[stat];
}

int Pokemon::getCurrentHP() {
	return mCurrentHP;
}

void Pokemon::setCurrentHP(int hp) {
	mCurrentHP = hp;
}

void Pokemon::takeDamage(int damage) { // TODO change so it returns the amount of actual damage taken for recoil moves
	int currentHP = getCurrentHP();
	int resultingHP = currentHP - damage;
	if (resultingHP < 0) {
		resultingHP = 0;
	}
	setCurrentHP(resultingHP);
}

void Pokemon::restoreHP(int healing) {
	int currentHP = getCurrentHP();
	int resultingHP = currentHP + healing;
	if (resultingHP > getStat(HP)) {
		resultingHP = getStat(HP);
	}
	setCurrentHP(resultingHP);
}

void Pokemon::fullyHeal() {
	setCurrentHP(getStat(HP));
}

bool Pokemon::isFainted() {
	if (getCurrentHP() < 1) {
		return true;
	}
	return false;
}

/**
 * Move getters and setters
 */
Move* Pokemon::getMove(MoveNum moveSlot) {
	return mMoves[moveSlot];
}

string Pokemon::getMoveName(MoveNum moveSlot) {
	return mMoves[moveSlot]->getMoveName();
}

vector<Move*> Pokemon::getMoves() {
	vector<Move*> moves;
	for (int i = MOVE_1; i != NUM_MOVES; i++) {
		if (getMoveName((MoveNum)i) != "PLACEHOLDER") {
			moves.push_back(mMoves[(MoveNum)i]);
		}
	}
	return moves;
}
/*Move** Pokemon::getMoves() {
	return mMoves;
}*/

vector<string> Pokemon::getMoveNames() {
	vector<string> moveNames;
	for (int i = MOVE_1; i != NUM_MOVES; i++) {
		string moveName = mMoves[(MoveNum)i]->getMoveName();
		if (moveName != "PLACEHOLDER") {
			moveNames.push_back(moveName);
		}
	}
	return moveNames;
}

void Pokemon::setMove(string moveName, MoveNum moveSlot) {
	try {
		mMoves[moveSlot] = MoveList.at(moveName);
	}
	catch (const out_of_range& e) {
		MoveList[moveName] = new Move(moveName);
		mMoves[moveSlot] = MoveList.at(moveName);
	}
}

void Pokemon::setMove(Move* move, MoveNum moveSlot) {
	mMoves[moveSlot] = move;
}

void Pokemon::setMoves(string moveNames[NUM_MOVES]) {
	for (int i = MOVE_1; i != NUM_MOVES; i++) {
		setMove(moveNames[i], (MoveNum)i);
	}
}

void Pokemon::setMoves(Move* moves[NUM_MOVES]) {
	for (int i = MOVE_1; i != NUM_MOVES; i++) {
		setMove(moves[i], (MoveNum)i);
	}
}

void Pokemon::setMoves(vector<string> moves) {
	for (int i = MOVE_1; i < moves.size(); i++) {
		setMove(moves[i], (MoveNum)i);
	}
}

void Pokemon::refillMove(MoveNum moveSlot) {
	int maxPP = mMoves[moveSlot]->getBasePP();
	setMovePP(maxPP, moveSlot);
}

void Pokemon::refillMoves() {
	for (int i = MOVE_1; i != NUM_MOVES; i++) {
		refillMove((MoveNum)i);
	}
}

int Pokemon::getMovePP(MoveNum moveSlot) {
	return mMovePP[moveSlot];
}

vector<int> Pokemon::getMovesPP() {
	vector<int> pps;
	for (int i = MOVE_1; i != NUM_MOVES; i++) {
		string moveName = mMoves[(MoveNum)i]->getMoveName();
		if (moveName != "PLACEHOLDER") {
			pps.push_back(getMovePP((MoveNum)i));
		}
	}
	return pps;
}

void Pokemon::setMovePP(int pp, MoveNum moveSlot) {
	mMovePP[moveSlot] = pp;
}

void Pokemon::decMovePP(MoveNum moveSlot) {
	int pp = getMovePP(moveSlot) - 1;
	setMovePP(pp, moveSlot);
}

// true if the pokemon already knows that move
bool Pokemon::alreadyKnows(string moveName) {
	vector<string> moveNames = getMoveNames();

	if (find(moveNames.begin(), moveNames.end(), moveName) != moveNames.end()) {
		return true;
	}
	return false;
}

void Pokemon::learnMove(string moveName, MoveNum moveSlot) {
	setMove(moveName, moveSlot);
	refillMove(moveSlot);
}

/**
 * Print information about the Pokemon object to console
 */
void Pokemon::print() {
	cout << mNickname << '\n';
	cout << "   Level " << mLevel << '\n';
	cout << "   ";
	mSpecies->print();
	cout << "   HP: " << getCurrentHP() << " / " << getStat(HP) << endl;
}


void Pokemon::printVerbose() {
	cout << mNickname << '\n';
	cout << "Level " << mLevel << '\n';

	mSpecies->printVerbose();

	cout << "--------- IVs ---------\n";
	cout << "     HP: " << mIVs[HP] << '\n';
	cout << "    Atk: " << mIVs[ATK] << '\n';
	cout << "    Def: " << mIVs[DEF] << '\n';
	cout << "  SpAtk: " << mIVs[SPATK] << '\n';
	cout << "  SpDef: " << mIVs[SPDEF] << '\n';
	cout << "    Spd: " << mIVs[SPD] << '\n';

	cout << "--------- EVs ---------\n";
	cout << "     HP: " << mEVs[HP] << '\n';
	cout << "    Atk: " << mEVs[ATK] << '\n';
	cout << "    Def: " << mEVs[DEF] << '\n';
	cout << "  SpAtk: " << mEVs[SPATK] << '\n';
	cout << "  SpDef: " << mEVs[SPDEF] << '\n';
	cout << "    Spd: " << mEVs[SPD] << '\n';

	cout << "--------- Stats ---------\n";
	cout << "     HP: " << getCurrentHP() << '\n';
	cout << "    Atk: " << mStats[ATK] << '\n';
	cout << "    Def: " << mStats[DEF] << '\n';
	cout << "  SpAtk: " << mStats[SPATK] << '\n';
	cout << "  SpDef: " << mStats[SPDEF] << '\n';
	cout << "    Spd: " << mStats[SPD] << '\n';

	cout << "--------- Moves ---------\n";
	for (int i = MOVE_1; i != NUM_MOVES; i++) {
		mMoves[i]->print();
		if (mMoves[i]->getMoveName() != "PLACEHOLDER") {
			cout << "  Current PP: " << getMovePP((MoveNum)i) << '\n';
		}
	}
}
