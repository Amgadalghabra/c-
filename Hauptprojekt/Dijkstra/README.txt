Einbinden des Dijkstra:

1. File entpacken und Verzeichnis "Dijkstra" über "Add Existing Directory" in das Projekt einbinden

- ein neues Header-, ein neues Implementations-File und diese README
- neue Klasse: Dijkstra

2. Initialisierung einer Dijkstra-Instanz:
string gtxtFile = PfadZumGtxtFile;
Dijkstra *d = new Disjkstra(gtxtFile);

- liest die Graphinformationen aus dem gtxt-File und initialisiert den Dijkstra-Algorithmus

3. Starten des Algorihmus zur Suche nach dem kürzesten Weg:

d->berechne_dijkstra(d->returnNextKnoten(startKnoten),d->returnNextKnoten(zielKnoten)); // berechnet den kuerzesten Weg
wegcoord=d->findeWeg();

- startKnoten und zielKnoten sind vom Typ pair<double, double>
- returnNextKnoten liefert den Knoten des Graphen, der am nächsten liegt
- wegcoord ist vom Typ vector<pair<double, double> >, enthält also alle Koordinatenpaare des gefundenen Weges

#######################################################################################################################
Format einer .gtxt Datei:

<Anzahl Knoten>
<Anzahl Kanten>
<1.Knoten X-Coord> <1.Knoten Y-Coord>
<2.Knoten X-Coord> <2.Knoten Y-Coord>
...
<1.Kante Quellknoten><1.Kante Zielknoten><1.Kante Gewicht>
<2.Kante Quellknoten><2.Kante Zielknoten><2.Kante Gewicht>
<3.Kante Quellknoten><3.Kante Zielknoten><3.Kante Gewicht>
....
