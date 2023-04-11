#ifndef TRAINER_H
#define TRAINER_H

#include <string>

#include "../PokemonInfo/Pokemon.h"

using namespace std;

class Trainer {
public:

	Trainer(string name);

	string getTrainerName();
	Pokemon** getPokemon();
	int getNumPokemon();
	int getNumUsablePokemon();

	Pokemon* getLead();


private:
	string mName;
	Pokemon* mPokemon[6];
	int mNumPokemon;
	int mNumUsablePokemon;
};




#endif
