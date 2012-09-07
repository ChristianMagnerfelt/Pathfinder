all: main.o csocket.o pathfinder.o
	g++ -o pathfinder main.o csocket.o pathfinder.o

main.o:	csocket.h
	g++ -c -std=c++0x main.cc

csocket.o: csocket.h
	g++ -c csocket.cc

pathfinder.o: pathfinder.h
	g++ -c -std=c++0x pathfinder.cc

clean:
	rm -f *.o pathfinder
