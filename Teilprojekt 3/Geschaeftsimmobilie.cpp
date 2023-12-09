/***********************************************

Geschaeftsimmobilie.cpp 

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 28.11.2022

***********************************************/

#include<iostream>
#include<fstream>
#include "Immobilie.h"
#include "Geschaeftsimmobilie.h"

using namespace std;

Geschaeftsimmobilie::Geschaeftsimmobilie() {}   //  Konstruktor

Geschaeftsimmobilie::~Geschaeftsimmobilie() {}  //  Destruktor

void Geschaeftsimmobilie::eingabe() {
    //  Die Eingabe Funktion fuer die Klasse Geschaeftsimmobilie
    cout << "Gib 1 ein, wenn in der Immobilie auch Wohnungen enthalten sind, sonst 0: ";
    cin >> also_apartment;
    for(int i = 0; i<1; i++) {
        if(also_apartment != "0" && also_apartment != "1") {
            //  nochmal eingeben, wenn die Eingabe nicht 0 und nicht 1 ist
            cout << "Gib 1 ein, wenn in der Immobilie auch Wohnungen enthalten sind, sonst 0: ";
            cin >> also_apartment;
            i--;
        }
    }

    Immobilie::eingabe();   //  Die Anweisungen aus der Funktion "eingabe" bringen
}
        
void Geschaeftsimmobilie::ausgabe(fstream& outputFile) {
    //  Die Ausgabe Funktion fuer die Klasse Geschaeftsimmobilie mit einem Parameter fuer die Output-Datei
    outputFile << "Geschaeft" << ":" << endl;   //  in der Output.txt schreiben
    Immobilie::ausgabe(outputFile); //  Die Anweisungen aus der Funktion "ausgabe" bringen
    if(also_apartment == "1") {
        //  wenn die Eingabe 1 ist
        outputFile << "Die Immobilie enthaelt auch Wohnungen." << endl; //  in der Output.txt schreiben
    }
    else {
        outputFile << "Die Immobilie enthaelt keine Wohnungen." << endl;    //  in der Output.txt schreiben
    }
}