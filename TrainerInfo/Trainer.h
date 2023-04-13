#ifndef TRAINER_H
#define TRAINER_H

#include <string>
#include <vector>

#include "../PokemonInfo/Pokemon.h"

using namespace std;

class Trainer {
public:

	Trainer(string name);
	Trainer(string name, vector<Pokemon*> party);

	string getTrainerName();
	vector<Pokemon*> getParty();
	int getNumPokemon();
	int getNumUsablePokemon();

	Pokemon* getLead();


private:
	string mName;
	vector<Pokemon*> mParty;
	int mNumPokemon;
	int mNumUsablePokemon;
};




#endif
