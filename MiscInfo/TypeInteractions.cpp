#include <iostream>

#include "TypeInteractions.h"

map<Type, map<Type, double>> TypeChart = {
	{ NORMAL, map<Type, double>{
		{ ROCK, 0.5 },
		{ GHOST, 0 },
		{ STEEL, 0.5 }
	}},
	{ FIGHTING, map<Type, double>{
		{ FLYING, 0.5 },
		{ POISON, 0.5 },
		{ ROCK, 2 },
		{ BUG, 0.5 },
		{ GHOST, 0 },
		{ STEEL, 2 },
		{ PSYCHIC, 0.5 },
		{ ICE, 2 },
		{ DARK, 2 },
		{ FAIRY, 0.5 }
	}},
	{ FLYING, map<Type, double>{
		{ FIGHTING, 2 },
		{ ROCK, 0.5 },
		{ BUG, 2 },
		{ STEEL, 0.5 },
		{ GRASS, 2 },
		{ ELECTRIC, 0.5 }
	}},
	{ POISON, map<Type, double>{
		{ POISON, 0.5 },
		{ GROUND, 0.5 },
		{ ROCK, 0.5 },
		{ GHOST, 0.5 },
		{ STEEL, 0 },
		{ GRASS, 2 },
		{ FAIRY, 2 }
	}},
	{ GROUND, map<Type, double>{
		{ FLYING, 0 },
		{ POISON, 2 },
		{ ROCK, 2 },
		{ BUG, 0.5 },
		{ STEEL, 2 },
		{ FIRE, 2 },
		{ GRASS, 0.5 },
		{ ELECTRIC, 2 }
	}},
	{ ROCK, map<Type, double>{
		{ FIGHTING, 0.5 },
		{ FLYING, 2 },
		{ GROUND, 0.5 },
		{ BUG, 2 },
		{ STEEL, 0.5 },
		{ FIRE, 2 },
		{ ICE, 2 }
	}},
	{ BUG, map<Type, double>{
		{ FIGHTING, 0.5 },
		{ FLYING, 0.5 },
		{ POISON, 0.5 },
		{ GHOST, 0.5 },
		{ STEEL, 0.5 },
		{ FIRE, 0.5 },
		{ GRASS, 2 },
		{ PSYCHIC, 2 },
		{ DARK, 2 },
		{ FAIRY, 0.5 }
	}},
	{ GHOST, map<Type, double>{
		{ NORMAL, 0 },
		{ GHOST, 2 },
		{ PSYCHIC, 2 },
		{ DARK, 0.5 }
	}},
	{ STEEL, map<Type, double>{
		{ ROCK, 2 },
		{ STEEL, 0.5 },
		{ FIRE, 0.5 },
		{ WATER, 0.5 },
		{ ELECTRIC, 0.5 },
		{ ICE, 2 },
		{ FAIRY, 2 }
	}},
	{ FIRE, map<Type, double>{
		{ ROCK, 0.5 },
		{ BUG, 2 },
		{ STEEL, 2 },
		{ FIRE, 0.5 },
		{ WATER, 0.5 },
		{ GRASS, 2 },
		{ ICE, 2 },
		{ DRAGON, 0.5 }
	}},
	{ WATER, map<Type, double>{
		{ GROUND, 2 },
		{ ROCK, 2 },
		{ FIRE, 2 },
		{ WATER, 0.5 },
		{ GRASS, 0.5 },
		{ DRAGON, 0.5 }
	}},
	{ GRASS, map<Type, double>{
		{ FLYING, 0.5 },
		{ POISON, 0.5 },
		{ GROUND, 2 },
		{ ROCK, 2 },
		{ BUG, 0.5 },
		{ STEEL, 0.5 },
		{ FIRE, 0.5 },
		{ WATER, 2 },
		{ GRASS, 0.5 },
		{ DRAGON, 0.5 }
	}},
	{ ELECTRIC, map<Type, double>{
		{ FLYING, 2 },
		{ GROUND, 0 },
		{ WATER, 2 },
		{ GRASS, 0.5 },
		{ ELECTRIC, 0.5 },
		{ DRAGON, 0.5 }
	}},
	{ PSYCHIC, map<Type, double>{
		{ FIGHTING, 2 },
		{ POISON, 2 },
		{ STEEL, 0.5 },
		{ PSYCHIC, 0.5 },
		{ DARK, 0 }
	}},
	{ ICE, map<Type, double>{
		{ FLYING, 2 },
		{ GROUND, 2 },
		{ STEEL, 0.5 },
		{ FIRE, 0.5 },
		{ WATER, 0.5 },
		{ GRASS, 2 },
		{ ICE, 0.5 },
		{ DRAGON, 2 }
	}},
	{ DRAGON, map<Type, double>{
		{ STEEL, 0.5 },
		{ DRAGON, 2 },
		{ FAIRY, 0 }
	}},
	{ DARK, map<Type, double>{
		{ FIGHTING, 0.5 },
		{ GHOST, 2 },
		{ PSYCHIC, 2 },
		{ DARK, 0.5 },
		{ FAIRY, 0.5 }
	}},
	{ FAIRY, map<Type, double>{
		{ FIGHTING, 2 },
		{ POISON, 0.5 },
		{ STEEL, 0.5 },
		{ FIRE, 0.5 },
		{ DRAGON, 2 },
		{ DARK, 2 }
	}}
};


/**
 * Get damage multiplier from one type to another
 * 
 * @param attacker - the Type of the attacking move
 * @param defender - the Type of the defending Pokemon
 * @return - value of damage multiplier
 */
double getMultiplier(Type attacker, Type defender) {
	double multiplier;
	try {
		multiplier = TypeChart.at(attacker).at(defender);
	}
	catch (const std::out_of_range& e) {
		multiplier = 1;
	}
	return multiplier;
}

/**
 * Get damage multiplier from one type to a two-typed Pokemon
 *
 * @param attacker - the Type of the attacking move
 * @param defender1 - one of the Types of the defending Pokemon
 * @param defender2 - the other Type of the defending Pokemon
 * @return - value of damage multiplier
 */
double getMultiplier(Type attacker, Type defender1, Type defender2) {
	return getMultiplier(attacker, defender1) * getMultiplier(attacker, defender2);
}

/**
 * Get a dictionary of damage multipliers for a two-typed Pokemon
 *
 * @param type1 - one of the Types of the defending Pokemon
 * @param type2 - the other Type of the defending Pokemon
 * @return - dictionary with damage values of all types
 */
map<Type, double> getWeaknesses(Type type1, Type type2) {
	map<Type, double> weaknesses;
	for (int i = NORMAL; i != NONE; i++) {
		weaknesses[(Type)i] = getMultiplier((Type)i, type1, type2);
	}
	return weaknesses;
}
