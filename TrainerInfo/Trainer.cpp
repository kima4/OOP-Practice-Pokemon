#include <iostream>
#include <string>

#include "Trainer.h"

using namespace std;

Trainer::Trainer(string name) : mName(name) {

}

Trainer::Trainer(string name, vector<Pokemon*> party) : mName(name), mParty(party) {
	mNumPokemon = party.size();
	//mNumUsablePokemon = mNumPokemon;
}


string Trainer::getTrainerName() {
	return mName;
}

vector<Pokemon*> Trainer::getParty() {
	return mParty;
}

int Trainer::getNumPokemon() {
	return mNumPokemon;
}

int Trainer::getNumUsablePokemon() {
	int usable = 0;
	for (int i = 0; i < mNumPokemon; i++) {
		if (mParty[i]->getCurrentHP() > 0) {
			usable++;
		}
	}
	return usable;
}

Pokemon* Trainer::getLead() {
	return mParty[0];
}