// Author: Timon Kapischke
// Last modified on 15.12.2020
// Projekt: Routenplaner
// Version: 2.0

#ifndef Dijkstra_H_ 
#define Dijkstra_H_

#include <utility>
#include <vector>
#include <queue>
#include <string>

struct Order // Sortierstruktur fuer die Priority Quere. Sortiert Paare nach dem 2. Eintrag in aufsteigender Reihenfolge (kleinste Eintrag ist ganz oben)
{
    bool operator()(std::pair<int, long int> const& a, std::pair<int, long int> const& b) const
    {
        return a.second > b.second || (a.second == b.second && a.first > b.first);
    }
};

class Dijkstra{

    public:		
		Dijkstra(std::string); // Konstruktor der String soll den Namen der Datei enthalten
		~Dijkstra(){};

		void berechne_dijkstra(int start, int ziel);        // berechnet den Weg zwischen 2 Punkten
		std::vector<std::pair<double, double> > findeWeg(); // gibt den Weg zwischen Start und Ziel aus
		int returnWeglaenge();                              // gibt die Laenge des kuerzesten Weges aus
        std::pair<double, double> returnKnoten(int);        // gibt die Koordinaten des i-ten Knotens aus
        int returnNextKnoten(std::pair<double, double>);    // gibt die Knotennummer des naechstgelegenen Knotens aus

    private:
        std::priority_queue <std::pair<int, long int>,std::vector<std::pair<int, long int> >, Order > pq; // <int Knoten, long int Gewicht>
        std::vector<std::pair<long int, int> > weg; // long int Gewicht, int Herkunft; speichert den Abstand vom Startknoten und den Vorgaenger jedes Knotens
        std::vector<bool> fertig;                   // speichert welcher Knoten schon besucht worden ist
        int startKnoten;                            // Startknotennummer in coordlist
        int zielKnoten;                             // Zielknotennummer in coordlist
        int weglaenge;                              // Laenge des kuerzesten Weges

        // Variablen und Funktionen für den internen Graph
        int AnzahlKanten;                                   // Anzahl der Kanten des Graphes
        int AnzahlKnoten;                                   // Anzahl der Knoten des Graphes
        std::vector<std::pair<double, double> > coordlist;  // Koordinaten jedes Knotens
        std::vector<std::pair<int, long int> > edgelist;    // Zielknoten und Gewicht jeder Kante
        std::vector<int> edgeOffsets;                       // Verweis auf die erste ausgehende Kante von jedem Knoten

        void einlesen(std::string s);                       // liest den Graphen aus einer Datei s ein
        double abstand(std::pair<double, double> a, std::pair<double, double> b); // brechnet den euklidischen Abstand
        std::vector<std::pair<int, long int> > adijazent(int n);    // gibt alle adijazente Knoten und dessen Kantengewichte in einem Vektor aus
	                             
};

#endif //Dijkstra_H_

