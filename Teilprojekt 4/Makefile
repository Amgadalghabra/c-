main: main.o Backtracking.o
	g++ main.o Backtracking.o -o main

main.o: Backtracking.h main.cpp
	g++ -c main.cpp

Backtracking.o: Backtracking.cpp Backtracking.h
	g++ -c Backtracking.cpp

clean:
	rm *.o main