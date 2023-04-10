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
	map<string, int> mIVs;

	// evs
	map<string, int> mEVs;


};




#endif
