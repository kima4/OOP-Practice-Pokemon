all: tests

tests: Testing.o Types.o TypeInteractions.o PokemonSpecies.o
	g++ -o tests Testing.o Types.o TypeInteractions.o PokemonSpecies.o

Testing.o: Testing.cpp Testing.h ../TypeInfo/Types.h
	g++ -c Testing.cpp

Types.o: ../TypeInfo/Types.cpp ../TypeInfo/Types.h
	g++ -c  ../TypeInfo/Types.cpp

TypeInteractions.o: ../TypeInfo/TypeInteractions.cpp ../TypeInfo/TypeInteractions.h ../TypeInfo/Types.h
	g++ -c ../TypeInfo/TypeInteractions.cpp

PokemonSpecies.o: ../PokemonInfo/PokemonSpecies.cpp ../PokemonInfo/PokemonSpecies.h ../TypeInfo/Types.h
	g++ -c ../PokemonInfo/PokemonSpecies.cpp

clean:
	rm -f *.o tests