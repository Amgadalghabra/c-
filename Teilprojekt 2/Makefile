main: main.o bbsort.o qsort.o
	g++ main.o bbsort.o qsort.o -o main

main.o: bbsort.h qsort.h main.cpp
	g++ -c main.cpp

bbsort.o: bbsort.cpp bbsort.h
	g++ -c bbsort.cpp

qsort.o: qsort.cpp qsort.h
	g++ -c qsort.cpp

clean:
	rm *.o main