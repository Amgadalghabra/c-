/***********************************************

Backtracking.h - Header-File von Backtracking.cpp

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 11.12.2022

***********************************************/

#ifndef BACKTRACKING_H    //  Wenn die Datei schon definiert wurde, dann überspringt alles und geht zum Ende #endif, sonst definieren und kompilieren
#define BACKTRACKING_H    //  Die Datei definieren und kompilieren

/*Backtracking hilft bei der Loesung eines allgemeinen Problems, 
indem es eine Loesung fuer das erste Teilproblem findet und dann rekursiv versucht, 
andere Teilprobleme basierend auf der Loesung des ersten Problems zu loesen.*/
class Backtracking {
    private:
        std::vector < std::tuple<int, int, int> > tuples; //  die moeglichen Spieltage
        std::vector <int> gameday;   //  index der richtigen Spieltage in tuples
        std::vector<std::vector<int> > matrix;  //   matrix enthaelt Anzahl der Spiele zwischen je zwei Teams
    
    public:
        Backtracking();
        ~Backtracking();
        void matrixx(int m);
        void listTuples(int m);
        void volleyball(int m);
        std::string output();
};
#endif