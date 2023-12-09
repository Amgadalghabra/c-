/***********************************************

bbsort.cpp - Hauptdatei von Bubblesort

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 12.11.2022

***********************************************/

#include"bbsort.h"

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