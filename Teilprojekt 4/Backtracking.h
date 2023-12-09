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
        Backtracking(); //  Konstruktor
        ~Backtracking();    //  Destruktor
        void matrixx(int m);    /*Die Funktion (matrixx) wird verwendet, um 2D Vektor (matrix genannt) zu erstellen 
        und sie mit Nullen zu initialisieren.*/
        
        void listTuples(int m); /*Die Funktion (listTuples) wird verwendet, um alle moeglichen Spieltage zu bestimmen 
        also die Spieltage die in die Frage kommen. Wir bekommen dann Liste von Tupel.*/
        
        void volleyball(int m); /*Die Funktion (volleyball) wird verwendet, um Loesung das Volleyball-Problem zu finden. 
        Wir finden erstmal Loesung fuer das erste Teilproblem und dann versuchen wir die Loesung der anderen Teilprobleme zu finden.*/
        
        std::string output();   /*Die Funktion (output) wird verwendet, um die Spieltage (Loesung des Problems) auszudrucken. 
        Wir nehmen die Index aus dem Vector (gamday) und drucken die entsprechenden Tupel aus.*/
};
#endif