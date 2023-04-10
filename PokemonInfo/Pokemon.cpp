#include <iostream>
#include <string>
#include <tuple>
#include <time.h>
#include <cstdlib>

#include "Pokemon.h"


Pokemon::Pokemon(string species, int level) : Pokemon::Pokemon(species, level, species) {}

Pokemon::Pokemon(string species, int level, string nickname) : PokemonSpecies(species) {
	setLevel(level);
	setNickname(nickname);
	initIVs();
	initEVs();
	initStats();
	setCurrentHP(getStat(0));
}


void Pokemon::initIVs() {
	srand(time(0));

	for (int i = 0; i < 6; i++) {
		mIVs[i] = rand() % 32;
	}
}

void Pokemon::initEVs() {
	for (int i = 0; i < 6; i++) {
		mEVs[i] = 0;
	}
}

void Pokemon::initStats() {
	mStats[0] = calcMaxHP();
	for (int i = 1; i < 6; i++) {
		mStats[i] = calcOtherStat(i);
	}
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


int Pokemon::getIVHP() {
	return mIVs[0];
}
int Pokemon::getIVAtk() {
	return mIVs[1];
}
int Pokemon::getIVDef() {
	return mIVs[2];
}
int Pokemon::getIVSpAtk() {
	return mIVs[3];
}
int Pokemon::getIVSpDef() {
	return mIVs[4];
}
int Pokemon::getIVSpd() {
	return mIVs[5];
}
int* Pokemon::getIVs() {
	return mIVs;
}


int Pokemon::getEVHP() {
	return mEVs[0];
}
int Pokemon::getEVAtk() {
	return mEVs[1];
}
int Pokemon::getEVDef() {
	return mEVs[2];
}
int Pokemon::getEVSpAtk() {
	return mEVs[3];
}
int Pokemon::getEVSpDef() {
	return mEVs[4];
}
int Pokemon::getEVSpd() {
	return mEVs[5];
}
int* Pokemon::getEVs() {
	return mEVs;
}

void Pokemon::setEVHP(int ev) {
	mEVs[0] = ev;
}
void Pokemon::setEVAtk(int ev) {
	mEVs[1] = ev;
}
void Pokemon::setEVDef(int ev) {
	mEVs[2] = ev;
}
void Pokemon::setEVSpAtk(int ev) {
	mEVs[3] = ev;
}
void Pokemon::setEVSpDef(int ev) {
	mEVs[4] = ev;
}
void Pokemon::setEVSpd(int ev) {
	mEVs[5] = ev;
}
void Pokemon::setEVs(int* evs) {
	setEVHP(evs[0]);
	setEVAtk(evs[1]);
	setEVDef(evs[2]);
	setEVSpAtk(evs[3]);
	setEVSpDef(evs[4]);
	setEVSpd(evs[5]);
}
void Pokemon::addEVs(int* evs) {
	setEVHP(getEVHP() + evs[0]);
	setEVAtk(getEVAtk() + evs[1]);
	setEVDef(getEVDef() + evs[2]);
	setEVSpAtk(getEVSpAtk() + evs[3]);
	setEVSpDef(getEVSpDef() + evs[4]);
	setEVSpd(getEVSpd() + evs[5]);
}



int Pokemon::calcMaxHP() {
	int maxHP = getBaseHP() * 2 + getIVHP() + (getEVHP() / 4);
	maxHP *= getLevel();
	maxHP /= 100;
	return maxHP + getLevel() + 10;
}

int Pokemon::calcOtherStat(int otherStat) {
	int stat = getBaseStats()[otherStat] * 2 + getIVs()[otherStat] + (getEVs()[otherStat] / 4);
	stat *= getLevel();
	stat /= 100;
	return stat + 5;
}

int Pokemon::getStat(int stat) {
	return mStats[stat];
}

int Pokemon::getCurrentHP() {
	return mCurrentHP;
}

void Pokemon::setCurrentHP(int hp) {
	mCurrentHP = hp;
}


void Pokemon::print() {

	cout << mNickname << '\n';
	cout << "Level " << mLevel << '\n';

	PokemonSpecies::print();

	cout << "--------- IVs ---------\n";
	cout << "     HP: " << mIVs[0] << '\n';
	cout << "    Atk: " << mIVs[1] << '\n';
	cout << "    Def: " << mIVs[2] << '\n';
	cout << "  SpAtk: " << mIVs[3] << '\n';
	cout << "  SpDef: " << mIVs[4] << '\n';
	cout << "    Spd: " << mIVs[5] << '\n';

	cout << "--------- EVs ---------\n";
	cout << "     HP: " << mEVs[0] << '\n';
	cout << "    Atk: " << mEVs[1] << '\n';
	cout << "    Def: " << mEVs[2] << '\n';
	cout << "  SpAtk: " << mEVs[3] << '\n';
	cout << "  SpDef: " << mEVs[4] << '\n';
	cout << "    Spd: " << mEVs[5] << '\n';

	cout << "--------- Stats ---------\n";
	cout << "     HP: " << getCurrentHP() << "/" << mStats[0] << '\n';
	cout << "    Atk: " << mStats[1] << '\n';
	cout << "    Def: " << mStats[2] << '\n';
	cout << "  SpAtk: " << mStats[3] << '\n';
	cout << "  SpDef: " << mStats[4] << '\n';
	cout << "    Spd: " << mStats[5] << '\n';
}
