#include <iostream>
#include <string>
#include <tuple>
#include <time.h>
#include <cstdlib>

#include "Pokemon.h"
#include "PokemonList.h"

Pokemon::Pokemon(string species, int level) {
	mSpecies = SpeciesList.at(species);
	setLevel(level);
	setNickname(species);
	setGender();
	initIVs();
	initEVs();
	initStats();
	setCurrentHP(getStat(HP));
	initMoves();
	refillMoves();
	resetStatChanges();
}

void Pokemon::initIVs() {
	//srand(time(0));

	for (int i = HP; i != NUM_STATS; i++) {
		mIVs[i] = rand() % 32;
	}
}

void Pokemon::initEVs() {
	for (int i = HP; i != NUM_STATS; i++) {
		mEVs[i] = 0;
	}
}

void Pokemon::initStats() {
	mStats[0] = calcMaxHP();
	for (int i = ATK; i != NUM_STATS; i++) {
		mStats[i] = calcOtherStat((Stat)i);
	}
}

void Pokemon::initMoves() {
	Move* move1 = new Move("PLACEHOLDER");
	Move* move2 = new Move("PLACEHOLDER");
	Move* move3 = new Move("PLACEHOLDER");
	Move* move4 = new Move("PLACEHOLDER");
	Move* moves[4] = { move1, move2, move3, move4 };

	setMoves(moves);
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
		if (GenderRatio <= gendVal) {
			mGender = MALE;
		}
		mGender = FEMALE;
	}
}

void Pokemon::setGender(Gender gender) {
	mGender = gender;
}


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

int Pokemon::getStatChange(Stat stat) {
	return mStatChanges[stat];
}

void Pokemon::setStatChange(Stat stat, int change) {
	mStatChanges[stat] = change;
}

void Pokemon::addStatChange(Stat stat, int change) {
	int prevChange = getStatChange(stat);
	setStatChange(stat, prevChange + change);
}

void Pokemon::resetStatChanges() {
	for (int i = 1; i < NUM_STATS; i++) {
		mStatChanges[i] = 0;
	}
}

Move* Pokemon::getMove(int moveSlot) {
	return mMoves[moveSlot];
}

Move** Pokemon::getMoves() {
	return mMoves;
}

void Pokemon::setMove(Move* move, int moveSlot) {
	mMoves[moveSlot] = move;
}

void Pokemon::setMoves(Move* moves[4]) {
	for (int i = 0; i < 4; i++) {
		setMove(moves[i], i);
	}
}

void Pokemon::refillMove(int moveSlot) {
	int maxPP = mMoves[moveSlot]->getBasePP();
	setMovePP(maxPP, moveSlot);
}

void Pokemon::refillMoves() {
	for (int i = 0; i < 4; i++) {
		refillMove(i);
	}
}

int Pokemon::getMovePP(int moveSlot) {
	return mMovePP[moveSlot];
}

void Pokemon::setMovePP(int pp, int moveSlot) {
	mMovePP[moveSlot] = pp;
}


void Pokemon::print() {

	cout << mNickname << '\n';
	cout << "Level " << mLevel << '\n';

	mSpecies->print();

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
	cout << "     HP: " << getCurrentHP() << "/" << mStats[HP] << '\n';
	cout << "    Atk: " << mStats[ATK] << " +" << mStatChanges[ATK] << '\n';
	cout << "    Def: " << mStats[DEF] << " +" << mStatChanges[DEF] << '\n';
	cout << "  SpAtk: " << mStats[SPATK] << " +" << mStatChanges[SPATK] << '\n';
	cout << "  SpDef: " << mStats[SPDEF] << " +" << mStatChanges[SPDEF] << '\n';
	cout << "    Spd: " << mStats[SPD] << " +" << mStatChanges[SPD] << '\n';

	cout << "--------- Moves ---------\n";
	for (int i = 0; i < 4; i++) {
		mMoves[i]->print();
		if (mMoves[i]->getMoveName() != "PLACEHOLDER") {
			cout << "  Current PP: " << getMovePP(i) << '\n';
		}
	}
}
