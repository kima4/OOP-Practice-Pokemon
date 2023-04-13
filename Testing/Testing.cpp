#include <iostream>
#include <tuple>
#include <time.h>
#include<cstdlib>

#include "Testing.h"
#include "../MiscInfo/Types.h"
#include "../MiscInfo/TypeInteractions.h"
//#include "../PokemonInfo/PokemonDatabase.h"
#include "../PokemonInfo/PokemonSpecies.h"
#include "../PokemonInfo/Pokemon.h"
#include "../MoveInfo/Move.h"
#include "../TrainerInfo/Trainer.h"
#include "../BattleInfo/BattleOverview.h"


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

//--------------------- PokemonInfo Tests ---------------------//

// creating bulbasaur and getting species
void BulbasaurSpecies() {
	PokemonSpecies* bulbasaur = new PokemonSpecies("Bulbasaur");
	string result = bulbasaur->getSpecies();
	string expected = "Bulbasaur";

	IS_TRUE(result == expected);
}

// fetching wigglytuff from database and checking types
void WigglytuffTypes() {
	PokemonSpecies* wigglytuff = new PokemonSpecies("Wigglytuff");
	Type* results;
	results = wigglytuff->getTypes();

	Type expected1 = NORMAL;
	Type expected2 = FAIRY;

	IS_TRUE(results[0] == expected1);
	IS_TRUE(results[1] == expected2);
}

// fetching arcanine from database and checking stats
void ArcanineStats() {
	PokemonSpecies* arcanine = new PokemonSpecies("Arcanine");
	int resultHP = arcanine->getBaseHP();
	int resultAtk = arcanine->getBaseAtk();
	int resultDef = arcanine->getBaseDef();
	int resultSpAtk = arcanine->getBaseSpAtk();
	int resultSpDef = arcanine->getBaseSpDef();
	int resultSpd = arcanine->getBaseSpd();

	int expectedHP = 90;
	int expectedAtk = 110;
	int expectedDef = 80;
	int expectedSpAtk = 100;
	int expectedSpDef = 80;
	int expectedSpd = 95;

	IS_TRUE(resultHP == expectedHP);
	IS_TRUE(resultAtk == expectedAtk);
	IS_TRUE(resultDef == expectedDef);
	IS_TRUE(resultSpAtk == expectedSpAtk);
	IS_TRUE(resultSpDef == expectedSpDef);
	IS_TRUE(resultSpd == expectedSpd);
}

// creating individual piloswine and checking level
void PiloswineIndividual() {
	Pokemon* piloswine = new Pokemon("Piloswine", 22);
	int result = piloswine->getLevel();
	int expected = 22;
	piloswine->print();
	IS_TRUE(result == expected);
}


//--------------------- MoveInfo Tests ---------------------//

// creating tackle and getting name
void CreateTackle() {
	Move* tackle = new Move("Tackle");
	string result = tackle->getMoveName();
	string expected = "Tackle";
	tackle->print();
	IS_TRUE(result == expected);
}

// creating individual staryu and moves
void StaryuMoves() {
	Pokemon* staryu = new Pokemon("Staryu", 43);
	staryu->learnMove("Water Gun", MOVE_1);
	int result = staryu->getMove(MOVE_1)->getBasePower();
	int expected = 40;
	staryu->print();
	IS_TRUE(result == expected);
}

// creating individual dragonite and checking move initiation
void DragoniteMoves() {
	Pokemon* dragonite = new Pokemon("Dragonite", 22);
	int result = dragonite->getMove(MOVE_1)->getBasePower();
	int expected = 0;
	dragonite->print();
	IS_TRUE(result == expected);
}


//--------------------- TrainerInfo Tests ---------------------//

void TrainerCreate() {
	vector<Pokemon*> party;
	Pokemon* rattata = new Pokemon("Rattata", 14);
	party.push_back(rattata);

	Trainer* trainer = new Trainer("George", party);

	vector<Pokemon*> result = trainer->getParty();
	
	IS_TRUE(result == party);
}


//--------------------- BattleInfo Tests ---------------------//

void BattleTest() {
	vector<Pokemon*> party;
	Pokemon* pidgey = new Pokemon("Pidgey", 6);
	party.push_back(pidgey);
	Trainer* trainer = new Trainer("Samantha", party);
	Pokemon* wild = new Pokemon("Mewtwo", 70);
	BattleOverview* battle = new BattleOverview(trainer, wild);
	string resultP = battle->getPlayerPokemon()->getSpecies()->getSpecies();
	string expectedP = "Pidgey";
	IS_TRUE(resultP == expectedP);

}

void ActionTypeCheck() {
	vector<Pokemon*> party;
	Pokemon* muk = new Pokemon("Muk", 84);
	party.push_back(muk);
	Trainer* trainer = new Trainer("Fred", party);
	Pokemon* wild = new Pokemon("Oddish", 15);
	BattleOverview* battle = new BattleOverview(trainer, wild);

	Action* action = battle->createAction(true, 3);

	ActionType expected = SWITCH;
	ActionType result = action->getActionType();
	IS_TRUE(result == expected);
}

void FightMoveChoice() {
	vector<Pokemon*> party;
	Pokemon* machamp = new Pokemon("Machamp", 92);
	party.push_back(machamp);
	Trainer* trainer = new Trainer("William", party);
	Pokemon* wild = new Pokemon("Sentret", 2);
	BattleOverview* battle = new BattleOverview(trainer, wild);
	battle->battle();
	/*Action* action = ;

	ActionType expected = FIGHT;
	ActionType result = action->getActionType();
	IS_TRUE(result == expected);*/
}


int main() {

	srand(time(0));
	/*
	cout << "------------------ TypeInfo Tests ------------------\n";

	ConvertFireToString();
	ConvertNoneToString();
	GroundToPoisonMultiplier();
	DarkToFightingMultiplier();
	NormalToGhostMultiplier();
	PsychicToNoneMultiplier();
	BulbasaurWeaknesses();
	MagnemiteWeaknesses();

	cout << "------------------ PokemonInfo Tests ------------------\n";

	BulbasaurSpecies();
	WigglytuffTypes();
	ArcanineStats();
	PiloswineIndividual();

	cout << "------------------ MoveInfo Tests ------------------\n";

	CreateTackle();
	StaryuMoves();
	DragoniteMoves();

	cout << "------------------ TrainerInfo Tests ------------------\n";

	TrainerCreate();

	cout << "------------------ BattleInfo Tests ------------------\n";

	BattleTest();
	ActionTypeCheck();*/
	FightMoveChoice();

	return 0;
}