/***********************************************

main.cpp - Hauptdatei von Teilprojekt 4

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 11.12.2022

***********************************************/

#include<iostream>
#include<fstream>
#include<vector>
#include<tuple>
#include "Backtracking.h"
#include "Timer.h"

using namespace std;

bool isNumber(string s) {
    //  ueberpruefen, ob s eine positive und ganze Zahl ist
    return s.find_first_not_of("0123456789") == string::npos;
}

int main() {
    //  main Funktion
    string m1;  //  Anzahl der Teams (String)
    int m;  //  Anzahl der Teams (Integer)
    cout << "Anzahl der Teams: ";
    cin >> m1;
    for(int i = 0; i<1; i++) {
        //	falls m String enthaelt oder m und m-1 nicht durch 3 teilbar sind oder m kleiner als 3 ist
        if(!isNumber(m1) || (stoi(m1)%3 != 0 && (stoi(m1)-1)%3 != 0) || stoi(m1) < 3) {
            cout << "FEHLER! Gib eine ganze Zahl m ab 3 ein! m oder m-1 muss durch 3 teilbar sein: ";
            cin >> m1;
            i--;    // Wiederholen, bis die Eingabe richtig ist
        }
    }
    m = stoi(m1);	//	m von String zu Integer umwandeln

    Timer timer;  //  Laufzeit messen
    timer.start();    //  starten
    
    Backtracking b;
    b.matrixx(m);
    b.listTuples(m);
    b.volleyball(m);
    string s = b.output();
    cout << s;
    
    timer.stop(); //  stoppen
    cout << "\nLaufzeit : " << timer.secs() << endl;  //  Laufzeit in Sekunden
}