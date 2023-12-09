/***********************************************

teilprojekt1.cpp - Hauptdatei von Teilprojekt 1

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 12.11.2022

***********************************************/

#include<iostream>
#include<getopt.h>

using namespace std;

//	Diese Funktion sortiert Arrays mithilfe von Bubblesort
void bubblesort(int array[], int arrayLength) {
	int i,j;
	for(i=0; i<arrayLength-1; i++) {
		for(j=0; j<arrayLength-i-1; j++) {
			//	Die Elemente tauschen
			if(array[j] > array[j+1]) {
				int k = array[j];
				array[j] = array[j+1];
				array[j+1] = k; 
			}
		}
	}
}

//	Diese Funktion sortiert Arrays mithilfe von Quicksort
void quicksort(int array[], int firstPosition, int lastPosition) {
	int pivot = array[lastPosition];	//	Pivotelement
	int i = firstPosition - 1;	//	i ist die Position, die vor dem ersten Element ist
	if (firstPosition < lastPosition) {	
		//	Das wird verwendet, um alle Elemente, die kleiner/grösser als das Pivotelement sind,
		//	vor/nach das Pivotelement zu bringen
		for (int j = firstPosition; j <= lastPosition - 1; j++) {
			if (array[j] < pivot) {	
				//	Elemente tauschen, nur wenn das Pivotelement grösser ist
				i++;
				int k = array[i];
				array[i] = array[j];
				array[j] = k;
			}
		}
		int k = array[i+1];	//	Das Pivotelement in der richtigen Position bringen
		array[i+1] = array[lastPosition];
		array[lastPosition] = k;
		quicksort(array, firstPosition, i);	//	Die Elemente sortieren, die vor dem Pivotelement sind
		quicksort(array, i + 2, lastPosition);	//	Die Elemente sortieren, die nach dem Pivotelement sind
	}
}

//	Prueft, ob ein String nur Integer enthält
bool isNumber(string str, string allowedString ,int index) {
    return str.find_first_not_of(allowedString, index) == string::npos;
}

//	main Funktion	
int main(int argc, char* argv[]) {
	int opt = 0;
	if((opt=getopt(argc,argv,"hn:")) != -1) {
		switch(opt) {
			case 'h':
				cout << "Benutzung: " << argv[0] << " -n [positive und ganze Zahl]" << endl;
				break;

			case 'n': 
				int n;	//	n ist der Anzahl der Elemente
				if(isNumber(argv[2],"0123456789",0)) {
					//	wenn es kein String in argv[2] gibt
					n = atoi(argv[2]);	//	waechselt String aus Kommandozeile in Integer 
					cout << "Geben Sie " << n << " ganze Zahlen ein und bestaetigen Sie nach jeder Zahl mit Enter:" << endl;
				}
				else {
					cout << "FEHLER!" << endl;
					cout << "Bitte geben sie ./teilprojekt1 -h ein" << endl;
					break; 
				}
	
				int bubbleArray[n];	//	Array um die Eingabe der Zahlen für Bubblesort zu speichern
				int quickArray[n];	//	Array um die Eingabe der Zahlen für Quicksort zu speichern
				int number;	//	um die aktuell eingegebene Zahl zu speichern
				string input;	//	die Eingabe
				for (int i=0; i<n; i++) { 
					//	zum Eintragen der einzugebenen Zahlen ins Array
					cin >> input;	//	Eingabe einer Zahl
					if(input.length() == 1) {
						//	wenn die eingegebene Zahl die laenge 1 hat
						if(isNumber(input,"0123456789",0)) {
							//	wenn die eingegebene Zahl nur Zahlen enthaelt
							number = stoi(input);	//	waechselt die Eingabe von String in Integer 
							quickArray[i] = number;	//	Eintrag in Array 
							bubbleArray[i] = number;	//	Eintrag in Array
						}
						else {
							cout << "FEHLER! Bitte geben Sie eine ganze Zahl ein: " << endl;
							i--;
						}
					}
					else {
						//	wenn die eingegebene Zahl nicht die laenge 1 hat
						if(isNumber(input,"0123456789",1) && isNumber(input,"-0123456789",0)) {
							//	wenn die eingegebene Zahl kein String enthaelt oder eine negative Zahl ist
							number = stoi(input);	//	waechselt die Eingabe von String in Integer
							quickArray[i] = number;	//	Eintrag in Array 
							bubbleArray[i] = number;	//	Eintrag in Array
						}
						else {
							cout << "FEHLER! Bitte geben Sie eine ganze Zahl ein: " << endl;
							i--;
						}
					}
				}		
				cout << "Das Array: ";
				for (int j=0; j<n-1; j++) {
					cout << bubbleArray[j] << ", ";
				}
				cout << bubbleArray[n-1] << endl;	//	Die letzte Zahl ausdrucken
				bubblesort(bubbleArray,n);
				cout << "mit Bubblesort sortieren: ";
				for (int k=0; k<n-1; k++) {
					cout << bubbleArray[k] << ", ";
				}
				cout << bubbleArray[n-1] << endl;	//	Die letzte sortierte Zahl ausdrucken
				
				quicksort(quickArray, 0,n-1);
				cout << "mit Quicksort sortieren: ";
				for (int p=0; p<n-1; p++) {
					cout << quickArray[p] << ", ";
				}
				cout << quickArray[n-1] << endl;	//	Die letzte sortierte Zahl ausdrucken
				
				break;
		}
	}

	else {
		cout << "Bitte geben sie ./teilprojekt1 -h ein" << endl;
	}
}