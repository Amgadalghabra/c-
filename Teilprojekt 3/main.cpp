/***********************************************

main.cpp - Hauptdatei von Teilprojekt 3

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 28.11.2022

***********************************************/

#include<iostream>
#include<fstream>
#include<vector>
#include "Immobilie.h"
#include "Wohnimmobilie.h"
#include "Geschaeftsimmobilie.h"

using namespace std;

//  main Funktion
int main() {
    vector <Immobilie*> data;   //  Vektor erstellen, um die Eingaben der Immobilien zu speichern
    
    cout << "Anzahl der Immobilien  : ";
    string n1;  //  n1 ist Anzahl der Immobilien als string
    cin >> n1;
    for(int i = 0; i<1; i++) {
        if(n1.find_first_not_of("0123456789") != string::npos) {
            //	wenn n1 keine natuerliche Zahl ist
            cout << "Anzahl der Immobilien  : ";
            cin >> n1;
            i--;
        }
    }
    int n = stoi(n1);	//	waechselt n1 von String in Integer n 
    
    string input;
    for(int i = 0; i<n; i++) {
        cout << endl << "Die " << i+1 << ". Immobilie :" << endl;
        cout << "Fuer Wohnimmobilie gib 1 ein und fuer Geschaeftsimmobilie gib 0 ein: ";
        cin >> input;
        if(input == "1") {
            //  wenn die Immobilie eine Wohnimmobilie ist 
            Immobilie* w = new Wohnimmobilie();
            w->eingabe();
            data.push_back(w); //  Die Eingabe für die Wohnimmobilie in dem Vektor speichern
        }
        else if(input == "0") {
            //  wenn die Immobilie eine Geschaeftsimmobilie ist 
            Immobilie* g = new Geschaeftsimmobilie();
            g->eingabe();
            data.push_back(g); //  Die Eingabe fuer die Geschaeftsimmobilie in dem Vektor speichern
        }
        else {
            //  wenn die Eingabe nicht 0 und nicht 1 ist dann nochmal eingeben
            i--;
        }

    }
    
    fstream outputFile;	//	Output-Datei erstellen
    outputFile.open("Output.txt",ios::out); //  oeffnen

    outputFile << "Es wurden " << data.size() << " Immobilien eingegeben" << endl;
    for (int i = data.size()-1; i>=0; i--) {
        //  Die Ausgabe in der Output.txt schreiben
        outputFile << "-------------"  << endl;
        data[i]->ausgabe(outputFile);
        cout << "-------------" << endl << "Das " << i+1 << ". ";
        delete data[i]; //  Objekt loeschen
    }
    outputFile.close();	//	die Output-Datei schliessen
        
    cout << "\nDie eingegebenen Immobilien wurden in der Output-Datei gespeichert!";
}