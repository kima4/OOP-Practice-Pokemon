#include <iostream>

#include "Testing.h"
#include "../TypeInfo/Types.h"
#include "../TypeInfo/TypeInteractions.h"



//--------------------- TypeInfo Tests ---------------------//

// conversion of Type to string
void ConvertFireToString() {
	string result = getTypeString(FIRE);
	string expected = "Fire";
	
	IS_TRUE(result == expected);
}

// conversion of Type to string
void ConvertNoneToString() {
	string result = getTypeString(NONE);
	string expected = "";

	IS_TRUE(result == expected);
}

// getting damage multiplier
void GroundToPoisonMultiplier() {
	double result = getMultiplier(GROUND, POISON);
	double expected = 2;

	IS_TRUE(result == expected);
}

// getting damage multiplier
void DarkToFightingMultiplier() {
	double result = getMultiplier(DARK, FIGHTING);
	double expected = 0.5;

	IS_TRUE(result == expected);
}

// getting damage multiplier
void NormalToGhostMultiplier() {
	double result = getMultiplier(NORMAL, GHOST);
	double expected = 0;

	IS_TRUE(result == expected);
}

// getting damage multiplier
void PsychicToNoneMultiplier() {
	double result = getMultiplier(PSYCHIC, NONE);
	double expected = 1;

	IS_TRUE(result == expected);
}

// getting weaknesses
void BulbasaurWeaknesses() {
	map<Type, double> result = getWeaknesses(GRASS, POISON);
	double expectedFire = 2;
	double expectedGrass = 0.25;
	double expectedWater = 0.5;
	double expectedNormal = 1;

	IS_TRUE(result.at(FIRE) == expectedFire);
	IS_TRUE(result.at(GRASS) == expectedGrass);
	IS_TRUE(result.at(WATER) == expectedWater);
	IS_TRUE(result.at(NORMAL) == expectedNormal);
}

// getting weaknesses
void MagnemiteWeaknesses() {
	map<Type, double> result = getWeaknesses(ELECTRIC, STEEL);
	double expectedFighting = 2;
	double expectedFlying = 0.25;
	double expectedRock = 0.5;
	double expectedDark = 1;
	double expectedGround = 4;
	double expectedPoison = 0;

	IS_TRUE(result.at(FIGHTING) == expectedFighting);
	IS_TRUE(result.at(FLYING) == expectedFlying);
	IS_TRUE(result.at(ROCK) == expectedRock);
	IS_TRUE(result.at(DARK) == expectedDark);
	IS_TRUE(result.at(GROUND) == expectedGround);
	IS_TRUE(result.at(POISON) == expectedPoison);
}


int main() {

	cout << "------------------ TypeInfo Tests ------------------\n";

	ConvertFireToString();
	ConvertNoneToString();
	GroundToPoisonMultiplier();
	DarkToFightingMultiplier();
	NormalToGhostMultiplier();
	PsychicToNoneMultiplier();
	BulbasaurWeaknesses();
	MagnemiteWeaknesses();


	return 0;
}