all: tests

tests: Testing.o Types.o
	g++ -o tests Testing.o Types.o

Testing.o: Testing.cpp Testing.h ../TypeInfo/Types.h
	g++ -c Testing.cpp

Types.o: ../TypeInfo/Types.cpp ../TypeInfo/Types.h
	g++ -c  ../TypeInfo/Types.cpp

clean:
	rm -f *.o tests