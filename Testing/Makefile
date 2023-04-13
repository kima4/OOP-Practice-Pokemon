all: tests

tests: Testing.o Types.o TypeInteractions.o PokemonSpecies.o Pokemon.o Move.o Trainer.o BattleOverview.o
	g++ -o tests Testing.o Types.o TypeInteractions.o PokemonSpecies.o Pokemon.o Move.o Trainer.o BattleOverview.o -g

Testing.o: Testing.cpp Testing.h ../MiscInfo/Types.h
	g++ -c Testing.cpp -g

Types.o: ../MiscInfo/Types.cpp ../MiscInfo/Types.h
	g++ -c ../MiscInfo/Types.cpp -g

TypeInteractions.o: ../MiscInfo/TypeInteractions.cpp ../MiscInfo/TypeInteractions.h ../MiscInfo/Types.h
	g++ -c ../MiscInfo/TypeInteractions.cpp -g

PokemonSpecies.o: ../PokemonInfo/PokemonSpecies.cpp ../PokemonInfo/PokemonSpecies.h ../MiscInfo/Types.h
	g++ -c ../PokemonInfo/PokemonSpecies.cpp -g

Pokemon.o: ../PokemonInfo/Pokemon.cpp ../PokemonInfo/Pokemon.h
	g++ -c ../PokemonInfo/Pokemon.cpp -g

Move.o: ../MoveInfo/Move.cpp ../MoveInfo/Move.h ../MoveInfo/MoveDatabase.h
	g++ -c ../MoveInfo/Move.cpp -g

Trainer.o: ../TrainerInfo/Trainer.cpp ../TrainerInfo/Trainer.h
	g++ -c ../TrainerInfo/Trainer.cpp -g

BattleOverview.o: ../BattleInfo/BattleOverview.cpp ../BattleInfo/BattleOverview.h
	g++ -c ../BattleInfo/BattleOverview.cpp -g

clean:
	rm -f *.o tests