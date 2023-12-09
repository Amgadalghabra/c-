/***********************************************

Backtracking.cpp 

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 11.12.2022

***********************************************/

#include<iostream>
#include<fstream>
#include<vector>
#include<tuple>
#include "Backtracking.h"

using namespace std;

Backtracking::Backtracking() {} //  Konstruktor
Backtracking::~Backtracking() {}    //  Destruktor

/*Die Funktion (matrixx) wird verwendet, 
um 2D Vektor (matrix genannt) zu erstellen und sie mit Nullen zu initialisieren.*/
void Backtracking::matrixx(int m) {    
    // Elemente in Vektor einfuegen 
    for (int i = 0; i < m+1; i++) { 
        // Vektor zum Speichern von Spaltenelementen 
        vector<int> v; 
        for (int j = 0; j < m+1; j++) { 
            v.push_back(0); 
        } 
        matrix.push_back(v);
    } 
}

/*Die Funktion (listTuples) wird verwendet, um alle moeglichen Spieltage zu bestimmen
also die Spieltage die in die Frage kommen. Wir bekommen dann Liste von Tupel*/
void Backtracking::listTuples(int m) {
    //  i ist gleich 1 und nicht 0, um nicht (0,1,2) zu bekommen sondern (1,2,3)
    for(int i = 1; i < m+1; i++) { 
        for(int j = i+1; j < m+1; j++) {
            for(int k = j+1; k < m+1; k++) {
                //  Tupel in Vektor einfuegen
                tuples.push_back(make_tuple(i, j, k));
            }
        }
    }
}

/*Die Funktion (volleyball) wird verwendet, um Loesung das Volleyball-Problem zu finden.
Wir finden erstmal Loesung fuer das erste Teilproblem und dann versuchen wir die Loesung der anderen Teilprobleme zu finden*/
void Backtracking::volleyball(int m) {
    //  Wenn Anzahl der Teams gleich 3 ist, dann gibt es nur eine einzige Loesung, die (1,2,3)(1,2,3) ist.
    if(m == 3) {
        gameday.push_back(0);
        gameday.push_back(0);
    }

    //  Wenn Anzahl der Teams groesser als 3 ist
    int i = 0;  // Fuer while Schleife
    int gauss = (m-2)*(m-1)/2;  //  Gaußsche Summenformel. Wir brauchen das, um zu rechnen, wie viele Tupel das Team 1 haben
    /*Wir versuchen jetzt das erste Teilproblem zu loesen. Wir suchen die Loesung für das Team 1,
    sodass das Team 1 gegen alle Teams insgesamt 2 Mal gespielt hat. Das hilft bessere Laufzeit zu kriegen.*/
    while (gameday.size() < m-1) {
        //  solange gameday nicht alle Indizes der gueltigen Spieltage hat. Das Team 1 muss in m-1 Tage spielen.  
        if (i == gauss) {
            //  bis zu Ende durchgelaufen, aber keine richtige Loesung erreicht
            i = gameday[gameday.size() - 1] + 1;    //  i zeigt auf das darauffolgende Tupel
            gameday.pop_back(); //  letzter Spieltag loeschen
            int t1 = get<0>(tuples[i-1]);   //  get<0> ist die erst Zahl in dem Tupel
            int t2 = get<1>(tuples[i-1]);   //  get<1> ist die zweite Zahl in dem Tupel
            int t3 = get<2>(tuples[i-1]);   //  get<2> ist die dritte Zahl in dem Tupel
            
            matrix[t1][t2] -= 1;    //  Anzahl der Begenungen zwischen t1 und t2 minus 1
            matrix[t1][t3] -= 1;    //  Anzahl der Begenungen zwischen t1 und t3 minus 1
            matrix[t2][t3] -= 1;    //  Anzahl der Begenungen zwischen t2 und t3 minus 1
            
            //  falls das vorletzte Tupel geloescht wurde            
            if (i == gauss) {               
                i = gameday[gameday.size() - 1] + 1;    //  i zeigt auf das darauffolgende Tupel
                gameday.pop_back(); //  letzter Spieltag loeschen
                t1 = get<0>(tuples[i-1]);   //  get<0> ist die erst Zahl in dem Tupel
                t2 = get<1>(tuples[i-1]);   //  get<1> ist die zweite Zahl in dem Tupel
                t3 = get<2>(tuples[i-1]);   //  get<2> ist die dritte Zahl in dem Tupel
    
                matrix[t1][t2] -= 1;    //  Anzahl der Begenungen zwischen t1 und t2 minus 1
                matrix[t1][t3] -= 1;    //  Anzahl der Begenungen zwischen t1 und t3 minus 1
                matrix[t2][t3] -= 1;    //  Anzahl der Begenungen zwischen t2 und t3 minus 1
            }

        }
        //  wenn i nich nicht beim letzten Tupel ist 
        int t1 = get<0>(tuples[i]); //  get<0> ist die erst Zahl in dem Tupel
        int t2 = get<1>(tuples[i]); //  get<1> ist die zweite Zahl in dem Tupel
        int t3 = get<2>(tuples[i]); //  get<2> ist die dritte Zahl in dem Tupel
        
        //  falls Anzahl der Begegnungen noch nicht 2 ist
        if(matrix[t1][t2] < 2 && matrix[t1][t3] < 2 && matrix[t2][t3] < 2) {
            gameday.push_back(i);   //  Spieltag einfuegen
            matrix[t1][t2] += 1;    //  Anzahl der Begenungen zwischen t1 und t2 plus 1
            matrix[t1][t3] += 1;    //  Anzahl der Begenungen zwischen t1 und t3 plus 1
            matrix[t2][t3] += 1;    //  Anzahl der Begenungen zwischen t2 und t3 plus 1
        }
        
        i += 1; //  Zur nächten Runde in der while Schleiche gehen 
    }

    /*Nachdem die Loesung des ersten Teilproblems (1 gegen alle Teams gespielt hat) gefunden wurde, 
    vsuchen wir die Loesung des gesamten Problems zu finden. Anfangen mit dem Tupel, der mit Team 2 anfaengt.*/ 
    while (gameday.size() < m*(m-1)/3) {
        //  solange gameday nicht alle Indizes der gueltigen Spieltage hat
        if (i == tuples.size()) {
            //  bis zu Ende durchgelaufen, aber keine richtige Loesung erreicht
            i = gameday[gameday.size() - 1] + 1;    //  i zeigt auf das darauffolgende Tupel
            gameday.pop_back(); //  letzter Spieltag loeschen
            int t1 = get<0>(tuples[i-1]);   //  get<0> ist die erst Zahl in dem Tupel
            int t2 = get<1>(tuples[i-1]);   //  get<1> ist die zweite Zahl in dem Tupel
            int t3 = get<2>(tuples[i-1]);   //  get<2> ist die dritte Zahl in dem Tupel
            
            matrix[t1][t2] -= 1;    //  Anzahl der Begenungen zwischen t1 und t2 minus 1
            matrix[t1][t3] -= 1;    //  Anzahl der Begenungen zwischen t1 und t3 minus 1
            matrix[t2][t3] -= 1;    //  Anzahl der Begenungen zwischen t2 und t3 minus 1
           
            //  falls das vorletzte Tupel geloescht wurde            
            if (i == tuples.size()) {               
                i = gameday[gameday.size() - 1] + 1;    //  i zeigt auf das darauffolgende Tupel
                gameday.pop_back(); //  letzter Spieltag loeschen
                t1 = get<0>(tuples[i-1]);   //  get<0> ist die erst Zahl in dem Tupel
                t2 = get<1>(tuples[i-1]);   //  get<1> ist die zweite Zahl in dem Tupel
                t3 = get<2>(tuples[i-1]);   //  get<2> ist die dritte Zahl in dem Tupel
    
                matrix[t1][t2] -= 1;    //  Anzahl der Begenungen zwischen t1 und t2 minus 1
                matrix[t1][t3] -= 1;    //  Anzahl der Begenungen zwischen t1 und t3 minus 1
                matrix[t2][t3] -= 1;    //  Anzahl der Begenungen zwischen t2 und t3 minus 1
            }

        }

        //  wenn i nich nicht beim letzten Tupel ist 
        int t1 = get<0>(tuples[i]); //  get<0> ist die erst Zahl in dem Tupel
        int t2 = get<1>(tuples[i]); //  get<1> ist die zweite Zahl in dem Tupel
        int t3 = get<2>(tuples[i]); //  get<2> ist die dritte Zahl in dem Tupel
        
        //  falls Anzahl der Begegnungen noch nicht 2 ist
        if(matrix[t1][t2] < 2 && matrix[t1][t3] < 2 && matrix[t2][t3] < 2) {    
            gameday.push_back(i);   //  Spieltag einfuegen
            matrix[t1][t2] += 1;    //  Anzahl der Begenungen zwischen t1 und t2 plus 1
            matrix[t1][t3] += 1;    //  Anzahl der Begenungen zwischen t1 und t3 plus 1
            matrix[t2][t3] += 1;    //  Anzahl der Begenungen zwischen t2 und t3 plus 1
        }
        
        i += 1; //  Zur nächten Runde in der while Schleiche gehen
    }

}

/*Die Funktion (output) wird verwendet, um die Spieltage (Loesung des Problems) auszudrucken.
Wir nehmen die Index aus dem Vector (gamday) und drucken die entsprechenden Tupel aus.*/
string Backtracking::output() {
    // Ausgabe
    string output = ""; //  Ein String, das die Loesung enthaelt
    for (int i = 0; i < gameday.size(); i++) {
        string s = to_string(get<0>(tuples[gameday[i]]));   //  to_string wird verwendt, um ein die erst Zahl in dem Tupel zu string umzuwandeln
        string s1 = to_string(get<1>(tuples[gameday[i]]));  //  to_string wird verwendt, um ein die zweite Zahl in dem Tupel zu string umzuwandeln
        string s2 = to_string(get<2>(tuples[gameday[i]]));  //  to_string wird verwendt, um ein die dritte Zahl in dem Tupel zu string umzuwandeln
        
        output += "(" + s + "," + s1 + "," + s2 + ")" + " ";    //  in output einfuegen
    }

    return output;
}
