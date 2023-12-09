/***********************************************

Wohnimmobilie.cpp 

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 28.11.2022

***********************************************/

#include<iostream>
#include<fstream>
#include "Wohnimmobilie.h"
#include "Immobilie.h"

using namespace std;

Wohnimmobilie::Wohnimmobilie() {}   //  Konstruktor

Wohnimmobilie::~Wohnimmobilie() {}  //  Destruktor

void Wohnimmobilie::eingabe() {
    //  Die Eingabe Funktion fuer die Klasse Wohnimmobilie
    cout << "Fuer Wohnung gib 1 ein und fuer Haus gib 0 ein: ";
    cin >> apartment_or_house;
    for(int i = 0; i<1; i++) {
        if(apartment_or_house != "0" && apartment_or_house != "1") {
            //  nochmal eingeben, wenn die Eingabe nicht 0 und nicht 1 ist
            cout << "Fuer Wohnung gib 1 ein und fuer Haus gib 0 ein: ";
            cin >> apartment_or_house;
            i--;
        }
    }
    if(apartment_or_house == "1") {
        //  wenn die Eingabe 1 ist dann "Wohnung" im string speichern
        apartment_or_house = "Wohnung";
    }
    else if(apartment_or_house == "0") {
        //  wenn die Eingabe 0 ist dann "Haus" im string speichern
        apartment_or_house = "Haus";
    }
            
    Immobilie::eingabe();   //  Die Anweisungen aus der Funktion "eingabe" bringen
}

void Wohnimmobilie::ausgabe(fstream& outputFile) {
    //  Die Ausgabe Funktion fuer die Klasse Wohnimmobilie mit einem Parameter fuer die Output-Datei
    outputFile << apartment_or_house << ":" << endl;    //  in der Output.txt schreiben
    Immobilie::ausgabe(outputFile); //  Die Anweisungen aus der Funktion "ausgabe" bringen
}