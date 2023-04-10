#include <string>
#include <tuple>
#include <time.h>
#include <cstdlib>

#include "Pokemon.h"


Pokemon::Pokemon(string species, int level) : PokemonSpecies(species) {
	setLevel(level);
}


void Pokemon::initIVs() {
	srand(time(0));

	

}



int Pokemon::getLevel() {
	return mLevel;
}

void Pokemon::setLevel(int level) {
	mLevel = level;
}
