/***********************************************

main.cpp - Hauptdatei von Teilprojekt 2

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 18.11.2022

***********************************************/

#include<iostream>
#include<getopt.h>
#include<fstream>
#include <vector>
#include"bbsort.h"
#include"qsort.h"

using namespace std;

//	main Funktion	
int main(int argc, char* argv[]) {
	int opt = 0;
	if((opt=getopt(argc,argv,"hn:")) != -1) {
		switch(opt) {
			case 'h':
				cout << "Benutzung: " << argv[0] << " -n [TXT-Datei]" << endl;
				cout << "Die TXT-Datei enthaelt die unsortierten Zahlen" << endl;
				break;

			case 'n': 
				ifstream inputFile(argv[2]);	//	Input-datei oeffnen
				if(!inputFile) {
					//	Wenn die Input-Datei nicht gefunden wurde
					cout << "Datei nicht gefunden!" << endl;
				}
				else {
					//	Wenn die Input-Datei gefunden wurde
					vector<int> v;	//	vektor v erstellen
					string line;	//	die Zahl als string
					int number;	//	die Zahl als integer
				
					while (getline(inputFile,line)) {
						//	die Input-datei Zeile nach Zeile lesen
						number = stoi(line);	//	waechselt die Zahl in der Zeile von String in Integer
						v.push_back(number);	//	die Zahl als integer in dem Vektor v speichern
					}
					inputFile.close();	//	die Input-datei schliessen
					int length = v.size();	//	length ist die laenge von dem Vektor v 

					int bubbleArray[length];	//	Array um die Zahlen aus der Input-datei fuer Bubblesort zu speichern
					int quickArray[length];	//	Array um die Zahlen aus der Input-datei fuer Quicksort zu speichern
				
					for (int i=0; i<length; i++) { 
						//	zum Eintragen der Zahlen ins Array 
						quickArray[i] = v[i];	//	Eintrag in Array 
						bubbleArray[i] = v[i];	//	Eintrag in Array
					}

					fstream outputFile;	//	Output-datei erstellen
					outputFile.open("Output.txt",ios::out);
					outputFile << "mit Bubblesort sortieren: ";	//	in der Output-datei schreiben
				
					bubblesort(bubbleArray,length);
					for (int k=0; k<length-1; k++) {
						//	die sortierte Zahlen einfuegen
						outputFile << bubbleArray[k] << ", ";
					}
					outputFile << bubbleArray[length-1] << endl;	//	Die letzte sortierte Zahl einfuegen

					quicksort(quickArray, 0,length-1);
					outputFile << "mit Quicksort sortieren: ";	//	in der Output-datei schreiben
					for (int p=0; p<length-1; p++) {
						//	die sortierte Zahlen einfuegen
						outputFile << quickArray[p] << ", ";
					}
					outputFile << quickArray[length-1] << endl;	//	Die letzte sortierte Zahl einfuegen
					outputFile.close();	//	die Input-datei schliessen
					cout << "Die sortierten Zahlen wurden in der Output-Datei gespeichert!";	//	wenn alles geklappt hat
					
					break;
				}
		}
	}

	else {
		cout << "Bitte geben sie ./main -h ein" << endl;
	}
}