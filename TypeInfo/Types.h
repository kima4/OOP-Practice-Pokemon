#ifndef TYPES_H
#define TYPES_H

#include <map>
#include <string>

using namespace std;

// all pokemon types
enum Type { NORMAL, FIGHTING, FLYING, POISON, GROUND, ROCK, BUG, GHOST, STEEL, FIRE, WATER, GRASS, ELECTRIC, PSYCHIC, ICE, DRAGON, DARK, FAIRY, NONE };

// for converting the Type enum to its equivalent string
extern map<Type, string> TypeStr;

// getting the string equivalent
string getTypeString(Type type);


#endif
