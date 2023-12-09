main: main.o Immobilie.o Wohnimmobilie.o Geschaeftsimmobilie.o
	g++ main.o Immobilie.o Wohnimmobilie.o Geschaeftsimmobilie.o -o main

main.o: Immobilie.h Wohnimmobilie.h Geschaeftsimmobilie.h main.cpp
	g++ -c main.cpp

Immobilie.o: Immobilie.cpp Immobilie.h
	g++ -c Immobilie.cpp

Wohnimmobilie.o: Wohnimmobilie.cpp Wohnimmobilie.h
	g++ -c Wohnimmobilie.cpp

Geschaeftsimmobilie.o: Geschaeftsimmobilie.cpp Geschaeftsimmobilie.h
	g++ -c Geschaeftsimmobilie.cpp

clean:
	rm *.o main