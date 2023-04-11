#include <iostream>
#include <string>

#include "Trainer.h"

using namespace std;

Trainer::Trainer(string name) : mName(name) {

}

string Trainer::getTrainerName() {
	return mName;
}

Pokemon** Trainer::getPokemon() {
	return mPokemon;
}

int Trainer::getNumPokemon() {
	return mNumPokemon;
}

int Trainer::getNumUsablePokemon() {
	return mNumUsablePokemon;
}

Pokemon* Trainer::getLead() {
	return mPokemon[0];
}