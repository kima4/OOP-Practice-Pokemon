all: pokemon

pokemon: main.o Types.o TypeInteractions.o PokemonSpecies.o Pokemon.o Move.o
	g++ -o pokemon main.o Types.o TypeInteractions.o PokemonSpecies.o Pokemon.o Move.o

main.o: main.cpp
	g++ -c main.cpp

Types.o: TypeInfo/Types.cpp TypeInfo/Types.h
	g++ -c TypeInfo/Types.cpp

TypeInteractions.o: TypeInfo/TypeInteractions.cpp TypeInfo/TypeInteractions.h TypeInfo/Types.h
	g++ -c TypeInfo/TypeInteractions.cpp

PokemonSpecies.o: PokemonInfo/PokemonSpecies.cpp PokemonInfo/PokemonSpecies.h TypeInfo/Types.h
	g++ -c PokemonInfo/PokemonSpecies.cpp

Pokemon.o: PokemonInfo/Pokemon.cpp PokemonInfo/Pokemon.h
	g++ -c PokemonInfo/Pokemon.cpp

Move.o: MoveInfo/Move.cpp MoveInfo/Move.h MoveInfo/MoveDatabase.h
	g++ -c MoveInfo/Move.cpp

clean: 
	rm -f *.o pokemon