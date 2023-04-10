#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <tuple>
#include <map>

#include "PokemonSpecies.h"

using namespace std;

class Pokemon : public PokemonSpecies {
public:
	Pokemon(string species, int level);

	void initIVs();

	int getLevel();
	void setLevel(int level);


private:
	unsigned int mLevel;

	// ivs
	int mIVs[6];

	// evs
	int mEVs[6];


};




#endif
