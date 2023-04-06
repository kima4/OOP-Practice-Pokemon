#ifndef TYPEINTERACTIONS_H
#define TYPEINTERACTIONS_H

#include "Types.h"

// type effectiveness chart - values not specified are neutral damage
extern map<Type, map<Type, double>> TypeChart;

// gets the damage multiplier based on the given types
double getMultiplier(Type attacker, Type defender);

// gets the damage multiplier list for the given types
map<Type, double> getWeaknesses(Type type1, Type type2);


#endif
