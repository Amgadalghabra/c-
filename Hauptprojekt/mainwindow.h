/***********************************************

mainwindow.h - Header-File von mainwindow.cpp

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 05.02.2023

***********************************************/

#ifndef MAINWINDOW_H    //  Wenn die Datei schon definiert wurde, dann ueberspringt alles und geht zum Ende #endif, sonst definieren und kompilieren
#define MAINWINDOW_H    //  Die Datei definieren und kompilieren

#include <QMainWindow>
#include "datamanager.h"
#include <QGraphicsScene>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QGraphicsPixmapItem>
#include <QUrl>
#include <Dijkstra/dijkstra.h>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*Die Klasse (MainWindow) wird verwendet, um ein Fenster fuer das Scheduler-Algorithmus zu erstellen.
Da koennen wir die Daten fuer jedes Teams eingeben, und sie in einem Datenbank speichern, und dann die Loesung ausgeben.*/
class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);  //  Konstruktor
        ~MainWindow();  //  Destruktor
        double long2Tile(int xTile, int z); // Kachelnummern in Laengengrad umrechnen
        double lat2Tile(int yTile, int z);  // Kachelnummern in Breitengrad umrechnen
        int x2Tile(double lon, int z);  // Laengengrad in Kachelnummern umrechnen
        int y2Tile(double lat, int z);  // Breitengrad in Kachelnummern umrechnen
        int xPixel(double lon, int z);  // in x-Pixelkoordinaten umrechnen
        int yPixel(double lat, int z);  // in y-Pixelkoordinaten umrechnen
        bool checkTeamNrExists(QString tableName, QString teamNr);  // ueberpruefen, ob Teamnummer existiert
        double teamCoordLon(QString teamNr);    // Laengengrad aus der Tabelle holen
        double teamCoordLat(QString teamNr);    // Breitengrad aus der Tabelle holen
        void route(QString teamNr1, QString teamNr2, int z);    // route auf der Karte
        void redrawTile(QNetworkReply *networkReply);
        void osmTiles(int z, int tileX, int tileY);

    private slots:
        void on_saveButton_clicked();   //  Button (Speichern)
        void on_solveButton_clicked();  //  Button (Berechnen)
        void on_deleteButton_clicked(); //  Button (Entfernen)
        void on_loadButton_clicked();   //  Button  (Tabelle laden)
        void on_helpButton_clicked();   //  Button (Hilfe)
        void on_mapButton_clicked();    //  Button (Ort Zeigen)
        void on_upButton_clicked();     //  Button (hoch)
        void on_downButton_clicked();   //  Button (runter)
        void on_rightButton_clicked();  //  Button (rechts)
        void on_leftButton_clicked();   //  Button (links)
        void on_zoomSlider_valueChanged(int value); //  Zoom Slider (nicht losgelassen)
        void on_zoomSlider_sliderReleased();    // Zoom Slider (losgelassen)
        void on_comboBox_currentIndexChanged(); // ComboBox (Spieltag)
        void on_helpKarteButton_clicked();

private:
        Ui::MainWindow *ui;
        DataManager datamanager;    // Objekt fuer die DataManager-Klasse
        QStringList list;  /* eine Liste von QString erstellen,
        der Teamsnummer enthaelt, die eingetragen wurden*/
        QString dbName = "Teams_database.db";   //  Name von der Datenbank
        QString tableName = "Teams";    //  Name von der Tabelle
        //  Die Spaltennamen in der Tabelle
        QString columnNames = "number INTEGER PRIMARY KEY,"
                              "name VARCHAR(30) NOT NULL,location VARCHAR(30) NOT NULL,"
                              "gameLocationLatitude DECIMAL NOT NULL,"
                              "gameLocationLongitude DECIMAL NOT NULL,"
                              "leader VARCHAR(30) NOT NULL";
        QString firstColumnName = "number"; //  Der erste Spaltenname
        QNetworkAccessManager *manager; /* Zeiger auf QNetworkAccessManager-Klasse.
        Diese Klasse wird verwendet, um Netzwerkanfragen zu senden und
        Antworten in einer Qt-Anwendung zu empfangen*/
        QHash<QNetworkReply*, int> networkReplyHash; /*"QHash<QNetworkReply*, int>"
        ist eine Deklaration fuer einen Hash-Container in Qt, der
        Netzwerkantworten (QNetworkReply*) als Schluessel und Integers
        als Werte speichert.*/
        QGraphicsScene myScene; /* Das myScene-Objekt wird verwendet,
        um die Elemente zu verwalten, die in einem QGraphicsView-Widget
        angezeigt werden.*/
        double longTile; // Koordinaten (Laengengrad)
        double latTile; // Koordinaten (Breitengrad)
        int xTile; // Kachelnummern (x)
        int yTile; // Kachelnummern (y)
        QVector<QPointF> pixelCoord; // Vektor,der Pixelkoordinaten des Weges hat

        Dijkstra *d; // Objekt fuer die Dijkstra-Klasse
        QString gtxtFile; // Fuer gtxt-File lesen
        bool openGtxtFile = false;
        int x0,y0; // Die erste x und y Tile

};
#endif // MAINWINDOW_H
