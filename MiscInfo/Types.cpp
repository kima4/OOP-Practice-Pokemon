#include <iostream>

#include "Types.h"

using namespace std;

map<Type, string> TypeStr = {
	{ NORMAL, "Normal" },
	{ FIGHTING, "Fighting" },
	{ FLYING, "Flying" },
	{ POISON, "Poison" },
	{ GROUND, "Ground" },
	{ ROCK, "Rock" },
	{ BUG, "Bug" },
	{ GHOST, "Ghost" },
	{ STEEL, "Steel" },
	{ FIRE, "Fire" },
	{ WATER, "Water" },
	{ GRASS, "Grass" },
	{ ELECTRIC, "Electric" },
	{ PSYCHIC, "Psychic" },
	{ ICE, "Ice" },
	{ DRAGON, "Dragon" },
	{ DARK, "Dark" },
	{ FAIRY, "Fairy" },
	{ NONE, "" }
};


string getTypeString(Type type) {
	return TypeStr.at(type);
}

