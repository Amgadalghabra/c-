/***********************************************

qsort.cpp - Hauptdatei von Quicksort

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 12.11.2022

***********************************************/

#include"qsort.h"

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