all: pokemon

pokemon: Types.o
	g++ -o pokemon Types.o

Types.o: TypeInfo/Types.cpp TypeInfo/Types.h
	g++ -c TypeInfo/Types.cpp

clean: rm -f *.o pokemon