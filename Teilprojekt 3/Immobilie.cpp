/***********************************************

Immobilie.cpp 

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 28.11.2022

***********************************************/

#include<iostream>
#include<fstream>
#include "Immobilie.h"
#include "Wohnimmobilie.h"
#include "Geschaeftsimmobilie.h"

using namespace std;

Immobilie::Immobilie() {}   //  Konstruktor

Immobilie::~Immobilie() {
    //  Destruktor
    cout << "Objekt geloescht!" << endl;
}

void Immobilie::eingabe() {
    //  Die Eingabe Funktion fuer die Klasse Immobilie    
    cout << "Adresse der Immobilie : ";
    cin.ignore();   //  Ignorieren, was im cin gespeichert ist (neue Zeile) 
    getline(cin,adresse);   //  Die Eingabe wird erst beendet, wenn eine neue Zeile eingefügt wird. 
                            //  Wird verwendet, um ein string ein Leerzeichen haben zu koennen
    cout << "Besitzer der Immobilie : ";
    getline(cin,besitzer);
    cout << "Baujahr der Immobilie : ";
    cin >> baujahr;
    for(int i = 0; i<1; i++) {
        if(baujahr.find_first_not_of("0123456789") != string::npos) {
            //	wenn es ein String in baujahr gibt
            cout << "Baujahr der Immobilie : ";
            cin >> baujahr;
            i--;
        }
    }
}

void Immobilie::ausgabe(fstream& outputFile) {    
    //  Die Ausgabe Funktion fuer die Klasse Immobilie mit einem Parameter fuer die Output-Datei     
    outputFile << "Adresse der Immobilie : " << adresse << endl;    //  in der Output.txt schreiben
    outputFile << "Besitzer der Immobilie : " << besitzer << endl;  //  in der Output.txt schreiben
    outputFile << "Baujahr der Immobilie : " << baujahr << endl;    //  in der Output.txt schreiben
}