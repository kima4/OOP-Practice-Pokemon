all: pokemon

pokemon: main.o Types.o TypeInteractions.o PokemonSpecies.o
	g++ -o pokemon main.o Types.o TypeInteractions.o PokemonSpecies.o

main.o: main.cpp
	g++ -c main.cpp

Types.o: TypeInfo/Types.cpp TypeInfo/Types.h
	g++ -c TypeInfo/Types.cpp

TypeInteractions.o: TypeInfo/TypeInteractions.cpp TypeInfo/TypeInteractions.h TypeInfo/Types.h
	g++ -c TypeInfo/TypeInteractions.cpp

PokemonSpecies.o: PokemonInfo/PokemonSpecies.cpp PokemonInfo/PokemonSpecies.h TypeInfo/Types.h
	g++ -c PokemonInfo/PokemonSpecies.cpp

clean: 
	rm -f *.o pokemon