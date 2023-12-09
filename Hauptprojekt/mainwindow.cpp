/***********************************************

mainwindow.cpp

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 05.02.2023

***********************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Backtracking.h"
#include <QMessageBox>
#include <algorithm>
#include <iostream>

using namespace std;

//  Konstruktor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    manager=new QNetworkAccessManager(this);
    // Datenbank und Tabelle erstellen
    datamanager.createDatabase(dbName);
    datamanager.createTable(tableName, columnNames);
    // Der connect Befehl zum Kartenzeichnen
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::redrawTile);
}

//  Destruktor
MainWindow::~MainWindow() {
    delete ui;
}

/*Die Funktion (on_helpButton_clicked) wird verwendet,
um der Button (Hilfe) einzustellen, und entscheiden was er machen muss,
wenn er geklickt wird.*/
void MainWindow::on_helpButton_clicked() {
    // Hilfe-Button wird verwendet, Um Hinweise zur Bedinung zu bekommen
    QMessageBox::information(this,"Information",
                             "Das Programm speichert die Teamdaten in einer "
                             "Tabelle.\n- Speichern-Button: Einfügen der "
                             "Teamdaten in die Tabelle.\n"
                             "- Entfernen-Button: "
                             "Löschen der Teamdaten aus der Tabelle. "
                             "(Hinweis für Entfernen-Button: Nur Teamnummer "
                             "muss angegeben werden!)\n"
                             "- Tabelle laden-Button: Teamdatei auswählen "
                             "und laden.\n"
                             "- Karte Zeigen-Button: gtxt-Datei auswählen "
                             "und laden.");
}

/*Die Funktion (on_saveButton_clicked) wird verwendet,
um der Button (Speichern) einzustellen, und entscheiden was er machen muss,
wenn er geklickt wird.*/
void MainWindow::on_saveButton_clicked() {
    /*wir erstellen number, name, location, coorGameLocationLat,
    coorGameLocationLong, leader als QString und
    werden die Daten von jedem Team haben*/
    QString number, name, location,
            coorGameLocationLat, coorGameLocationLong, leader;
    number = ui->numberBox->text();
    name = ui->nameLineEdit->text();
    location = ui->locationLineEdit->text();
    coorGameLocationLat = ui->LatSpinBox->text();
    coorGameLocationLong = ui->LongSpinBox->text();
    leader = ui->leaderLineEdit->text();

    // Wenn der Datensatz eingefuegt wird
    if(datamanager.insertRecord(tableName, number, name, location,
                                coorGameLocationLat, coorGameLocationLong,
                                leader)) {
        // dann wird "gespeichert!" ausgedruckt
        QMessageBox::information(this,"Speichern", "gespeichert!");
        //  Die Methode schowTable() aufrufen, um die Tabelle zu aktualisieren
        datamanager.showTable(tableName, ui->tableView, ui->listView);
    }
    //  sonst
    else {
        QMessageBox::critical(this,"Fehler", "existiert schon!");
        datamanager.showTable(tableName, ui->tableView, ui->listView);
    }
}

/*Die Funktion (on_deleteButton_clicked) wird verwendet,
um der Button (Entfernen) einzustellen, und entscheiden was er machen muss,
wenn er geklickt wird.*/
void MainWindow::on_deleteButton_clicked() {
    /*wir erstellen number als QString, um die Teamsnummer zu speichern.*/
    QString number;
    number = ui->numberBox->text();

    // Wenn der Datensatz geloescht wird
    if(datamanager.deleteRecord(tableName, firstColumnName, number)) {
        // dann wird "entfernt!" ausgedruckt
        QMessageBox::information(this,"Entfernen", "entfernt!");
        //  Die Methode schowTable() aufrufen, um die Tabelle zu aktualisieren
        datamanager.showTable(tableName, ui->tableView, ui->listView);
    }
    //  sonst
    else {
        QMessageBox::critical(this,"Fehler", "existiert nicht!");
        datamanager.showTable(tableName, ui->tableView, ui->listView);
    }
}

/*Die Funktion (on_loadButton_clicked) wird verwendet,
um der Button (Tabelle laden) einzustellen, und entscheiden was er machen muss,
wenn er geklickt wird.*/
void MainWindow::on_loadButton_clicked() {
    // Datenbankname
    QString fileName = QFileDialog::getOpenFileName(this, "Teamdatei öffnen",
                                                         "/home",
                                                         "(*.db)");
    if (!fileName.isEmpty()) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(fileName);
        if (db.open()) {
            // Tabellennamen erhalten
            QStringList tables = db.tables();
            // Tabellennamen auswaehlen
            QString tablename = tables.at(0);
            tableName = tablename;
            dbName = fileName;

            datamanager.showTable(tablename, ui->tableView, ui->listView);
        }
    }
    else {
        /*wir rufen aus der Klasse DataManager die Methode showTable() auf,
        um die Datensaetze in der Tabelle anzuzeigen.*/
        datamanager.showTable(tableName, ui->tableView, ui->listView);
    }
}

/*Diese Funktion wird verwendet, um zu ueberpruefen,
ob ein Element in B, in A existiert.*/
bool isSubset(QStringList A, QStringList B) {
    for(int j = 0; j < B.size(); j++) {
        //  wenn das Element in A nicht existiert<
        if(std::find (A.begin(), A.end(), B[j]) == A.end()) {
            return false;
        }
    }
    return true;
}

/*Diese Funktion wird verwendet,
um die Anzahl der Vorkommen von number in numbers zu zaehlen*/
bool is_unique(QStringList numbers) {
    /*Wenn die Anzahl groeßer als 1 ist, kommt number mehrmals vor
    und die Funktion gibt false zurueck.
    Andernfalls kommt number nur einmal vor und die Funktion gibt true zurueck.*/
    for(int i = 0; i < numbers.size(); i++) {
        if(std::count(numbers.begin(), numbers.end(), numbers[i]) != 1) {
            return false;
        }
    }
    return true;
}

/*Diese Funktion wird verwendet, um zu ueberpruefen,
ob x eine positive und ganze Zahl ist.*/
bool isNumber(QStringList x) {
    for(int i = 0; i < x.size(); i++) {
        //  wenn nicht
        if(x[i].isEmpty()) {
            return false;
        }
    }
    return true;
}

/*Die Funktion (on_solveButton_clicked) wird verwendet,
um der Button (Berechnen) einzustellen,
und entscheiden was er machen muss, wenn er geklickt wird.*/
void MainWindow::on_solveButton_clicked() {
    /*Die Teamsnummern aus der Eingabefeld in "str" speichern,
    fuer die zulaessiges Schedule berechnet werden soll*/
    QString str = ui->inputTextEdit->toPlainText();
    /*Die Teamsnummern aus str in der Liste "list1" einfuegen,
    und "\n" ignorieren*/
    QStringList list1 = str.split("\n");

    //  Die Liste "list" leeren
    list.clear();
    /*wir rufen aus der Klasse DataManager die Methode showTable() auf,
    um die Datensaetze in der Tabelle anzuzeigen.*/
    datamanager.showTable(tableName, ui->tableView, ui->listView);

    /*Das iteriert ueber alle Zeilen des Datenmodells,
    das dem QListView-Objekt "listView" zugewiesen ist,
    und fuegt jeden Wert in der ersten Spalte (Index 0) in eine Liste
    mit dem Namen "list" ein, wenn der Wert eindeutig (is_unique) ist.*/
    QAbstractItemModel *model = ui->listView->model();
    for (int row = 0; row < model->rowCount(); row++) {
        if(is_unique(list)) {
            list.append(model->data(model->index(row, 0)).toString());
        }
    }

    //  Wenn "list1" nicht nur Zahlen enthaelt
    if (!isNumber(list1)) {
        QMessageBox::critical(this,"Fehler", "Sie haben Enter gedrueckt "
                                             "nach dem Sie die letzte Eingabe "
                                             "eingegeben haben! "
                                             "Bitte pruefen Sie Ihre Eingabe.");
        qInfo() << list1;
    }
    /*Wenn "list1" eine Teamsnummer enthaelt, die nicht schon eingegeben
    und in "list" gespeichert wurde oder wenn in dem Eingabefeld
    eine Teamsnummer existiert, die mindestens zwei mal eingegeben wurde*/
    else if (!isSubset(list,list1) || !is_unique(list1)) {
        QMessageBox::critical(this,"Fehler", "Eine Teamnummer geht nicht "
                                             "oder existiert schon! "
                                             "Pruefen Sie Ihre Eingabe.");
        qInfo() << list1;
    }
    /*wenn Anzahl der Teams m und m-1 nicht durch 3 teilbar sind
    oder m kleiner als 3 ist*/
    else if ((list1.size()%3 != 0 && ((list1.size()-1)%3 != 0)) || list1.size() < 3) {
        QMessageBox::critical(this,"Fehler", "Anzahl der Teams muss eine ganze "
                                             "Zahl ab 3 und durch 3 teilbar "
                                             "sein!");
    }

    //  sonst alles gut
    else {
        /*TextEdit, das die Loesung (Spieltage) enthaelt, muss immer leer erst
        sein, bevor die neue Loesung ausgedruckt wird*/
        ui->textEdit_3->clear();

        // "gamedays" wird die Soieltage enthalten
        QString gamedays;

        /* "teamnr" enthaelt die Teamnummer. Die linke Seite ist ein Zaehler
        und die rechte Seite enhaelt die richtige Teamnummer. */
        std::vector<std::pair<QString, QString> > teamnr;
        for(int i = 0; i<list1.size(); i++) {
            teamnr.push_back(std::make_pair(QString::number(i+1),list1[i]));
        }
        //  das ausdrucken
        ui->textEdit_3->insertPlainText("Der Spielplan ist:\n");

        // Backtracking Klasse aufrufen und Anzahl der Teams eingeben
        Backtracking backtracking;
        backtracking.matrixx(list1.size());
        backtracking.listTuples(list1.size());
        backtracking.volleyball(list1.size());
        std::string s = backtracking.output();
        /*qString wird verwendet,
        um die Ausgabe in dem TextEdit ausdrucken zu koennen*/
        QString qString = QString(s.c_str());

        /* Hier tauscht das Programm die Teamnummer (1,2,3,4..) mit den
        richtigen Teamnummern (5,3,7,..) und speichert in "gamedays"*/
        for (int i = 0; i < qString.length(); i++) {
            for (int j = 0; j < teamnr.size(); j++) {
                /*Wenn das String mit der linken Seite vom Vektor "teamnr"
                uebereinstimmt, dann nehmen wir die Teamnummer
                von der rechten Seite*/
                if (qString[i] == teamnr[j].first) {
                    gamedays += teamnr[j].second;
                    break;
                }
                else {
                    /* wenn der ganze Vektor "teamnr" erreicht ist,
                    und das String nicht existiert*/
                    if (j == teamnr.size()-1) {
                        gamedays += qString[i];
                    }
                }
            }
        }
        // Spielplan zeigen
        ui->textEdit_3->insertPlainText(gamedays);

        // immer ComboBox "Spieltag" leeren nach jeder Berechnung
        ui->comboBox->clear();
        /* es wird eine List erstellt, um die Leerzeichnen zwischen
        den Spieltagen zu entfernen*/
        QStringList list = gamedays.split(" ");
        // Leerzeichen am Ende der Liste entfernen
        list.pop_back();
        // Die Spieltage in "Spieltag" anzeigen
        ui->comboBox->addItems(list);
    }
}

/* Die Funktion (on_comboBox_currentIndexChanged) wird aufgerufen,
um die Klammer und Komma von einem Spieltag (z.B. (1,2,3)) zu entfernen,
und die Teamnummer in "TeamNrBox" anzeigen.*/
void MainWindow::on_comboBox_currentIndexChanged() {
    ui->TeamNrBox->clear();
    // "selectedgameday" ist der ausgewaehlte Spieltag
    QString selectedgameday = ui->comboBox->currentText();
    // Klammer und Komma loeschen
    QStringList numbersList = selectedgameday.remove("(").remove(")").split(",");
    // Die Teamnummer in "TeamNrBox" anzeigen
    ui->TeamNrBox->addItems(numbersList);
}

/*Die Funktion (long2Tile) wird verwendet,
um die Laengenkoordinate eines bestimmten Kachelpunktes basierend auf der
Kachelnummer (xTile) und der Zoomstufe (z) zu berechnen.*/
double MainWindow::long2Tile(int xTile, int z) {
    return (double)((xTile / pow(2, z) * 360.0) - 180);
}

/*Die Funktion (lat2Tile) wird verwendet,
um die Breitenkoordinate  eines bestimmten Kachelpunktes basierend auf der
Kachelnummer (yTile) und der Zoomstufe (z) zu berechnen.*/
double MainWindow::lat2Tile(int yTile, int z) {
    return (double)(atan(sinh(M_PI * (1 - 2 * yTile / pow(2, z)))) * 180.0 / M_PI);
}

/*Die Funktion (x2Tile) wird verwendet,
um die die Kachelnummer auf der x-Achse (horizontal) basierend auf der
Laengenkoordinate (lon) und der Zoomstufe (z) zu berechnen.*/
int MainWindow::x2Tile(double lon, int z) {
    return (int)(floor((lon + 180.0) / 360.0 * pow(2.0, z)));
}

/*Die Funktion (y2Tile) wird verwendet,
um die die Kachelnummer auf der y-Achse (vertikal) basierend auf der
Breitenkoordinate (lat) und der Zoomstufe (z) zu berechnen.*/
int MainWindow::y2Tile(double lat, int z) {
    return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z)));
}

/*Die Funktion (xPixel) wird verwendet,
um die x-Pixelkoordinaten von der Karte zu rechnen.*/
int MainWindow::xPixel(double lon, int z) {
    // "lon" zu x-Tile umrechnen
    int x = x2Tile(lon,z);
    /* x-Tile wieder zu laengengrad umrechnen,
    um laengengrad von oben links zu bekommen*/
    double long1 = long2Tile(x,z);
    // laengengrad von oben rechts
    double long2 = long2Tile(x+1,z);
    return (int)(floor(((long1 - lon)/(long1 - long2))*256));
}

/*Die Funktion (yPixel) wird verwendet,
um die y-Pixelkoordinaten von der Karte zu rechnen.*/
int MainWindow::yPixel(double lat, int z) {
    // "lat" zu y-Tile umrechnen
    int y = y2Tile(lat,z);
    /* y-Tile wieder zu breitengrad umrechnen,
    um breitengrad von oben links zu bekommen*/
    double lat1 = lat2Tile(y,z);
    // breitengrad von oben rechts
    double lat2 = lat2Tile(y+1,z);
    return (int)(floor(((lat1 - lat)/(lat1 - lat2))*256));
}

/* Die Funktion (checkTeamNrExists) ueberprueft, ob eine bestimmte Teamnummer
in einer bestimmten Tabelle in einer SQL-Datenbank vorhanden ist.*/
bool MainWindow::checkTeamNrExists(QString tableName, QString teamNr) {
    /* Dies erstellt ein Objekt vom Typ "QSqlQuery",
    welches verwendet wird, um die SQL-Abfrage auszufuehren.*/
    QSqlQuery query;
    /* SQL-Abfrage vorbereiten, die die Anzahl der Eintraege in der angegebenen
    Tabelle mit der angegebenen Teamnummer zaehlt.*/
    query.prepare("SELECT COUNT(*) FROM " + tableName + " WHERE number = :teamNr");
    /* Dies bindet den Wert der Variablen "teamNr"
    an den Platzhalter in der Abfrage.*/
    query.bindValue(":teamNr", teamNr);
    // Dies fuehrt die vorbereitete Abfrage aus
    query.exec();
    // Dies setzt den Datensatzzeiger auf den ersten Datensatz der Ergebnismenge
    query.first();
    return query.value(0).toInt() > 0;
}

/* Die Funktion (teamCoordLon) holt den Laengengrad
von einem eingegebenen Teamnummer aus der Tabelle.*/
double MainWindow::teamCoordLon(QString teamNr) {
    /* Dies erstellt ein Objekt vom Typ "QSqlQuery",
    welches verwendet wird, um die SQL-Abfrage auszufuehren.*/
    QSqlQuery query;
    /* SQL-Abfrage vorbereiten, die der Laengengrad vom "TeamNr"
    aus der Tabelle nimmt.*/
    query.prepare("SELECT gameLocationLongitude FROM " + tableName + " WHERE number = " + "'"+teamNr+"'");

    QString longValue;
    /*Wenn die Abfrage fehlschlägt,
    wird eine Fehlermeldung in den Debug-Ausgaben ausgegeben*/
    if (!query.exec()) {
        qDebug() << "Error: fetching value failed";
    }
    /*Wenn die Abfrage erfolgreich ist, wird in einer Schleife jeder Datensatz
    durchlaufen und der Wert in "longValue" gespeichert.*/
    else {
        while (query.next()) {
            longValue = query.value(0).toString();
        }
    }

    // Wert der Koordinaten von "," zu "." umwandeln
    QString longValueDot = longValue.replace(',', '.');
    // Die Koordinaten in "longTile" und "latTile" speichern
    double lon = longValueDot.toDouble();

    return lon;
}

/* Die Funktion (teamCoordLat) holt den Breitengrad
von einem eingegebenen Teamnummer aus der Tabelle.*/
double MainWindow::teamCoordLat(QString teamNr) {
    /* Dies erstellt ein Objekt vom Typ "QSqlQuery",
    welches verwendet wird, um die SQL-Abfrage auszufuehren.*/
    QSqlQuery query;
    /* SQL-Abfrage vorbereiten, die der Breitengrad vom "TeamNr"
    aus der Tabelle nimmt.*/
    query.prepare("SELECT gameLocationLatitude FROM " + tableName + " WHERE number = " + "'"+teamNr+"'");

    QString latValue;
    /*Wenn die Abfrage fehlschlägt,
    wird eine Fehlermeldung in den Debug-Ausgaben ausgegeben*/
    if (!query.exec()) {
        qDebug() << "Error: fetching value failed";
    }
    /*Wenn die Abfrage erfolgreich ist, wird in einer Schleife jeder Datensatz
    durchlaufen und der Wert in "latValue" gespeichert.*/
    else {
        while (query.next()) {
            latValue = query.value(0).toString();
        }
    }

    // Wert der Koordinaten von "," zu "." umwandeln
    QString latValueDot = latValue.replace(',', '.');
    // Die Koordinaten in "longTile" und "latTile" speichern
    double lat = latValueDot.toDouble();

    return lat;
}

/*Die Funktion (route) wird verwendet, um den kuerzesten Weg zwischen zwei
Teams als Pixel zu bestimmen */
void MainWindow::route(QString teamNr1, QString teamNr2, int z) {
    // berechnet den kuerzesten Weg
    // startKnoten und zielKnoten
    d->berechne_dijkstra(d->returnNextKnoten(pair<double,double>
                                             (teamCoordLon(teamNr1),
                                              teamCoordLat(teamNr1))),
                         d->returnNextKnoten(pair<double,double>
                                             (teamCoordLon(teamNr2),
                                              teamCoordLat(teamNr2))));

    // wegcoord enthaelt also alle Koordinatenpaare des gefundenen Weges
    std::vector<std::pair<double, double> > wegcoord;
    wegcoord=d->findeWeg();
    // Vektor "pixelCoord" leeren vor jedder Ausfuellung
    pixelCoord.clear();

    // Laengen-BreitenGrad von dem Weg in "lons" und "lats" speichern
    std::vector<double> lons;
    std::vector<double> lats;
    for (int i = 0; i<wegcoord.size(); i++) {
        lons.push_back(wegcoord[i].first);
        lats.push_back(wegcoord[i].second);
    }

    // hier wird bestimmt, in welchem Tile (von 9 Tiles) die Markierung ist
    for (int i = 0; i<lons.size(); i++) {
        int x1 = x2Tile(lons[i],z);
        int xp = xPixel(lons[i],z);

        int y1 = y2Tile(lats[i],z);
        int yp = yPixel(lats[i],z);

        // in der ersten Zeile, zweiten Spalte
        if (x1-x0 == 1) {
            xp = xp+256;
        }
        // in der ersten Zeile, dritten Spalte
        if (x1-x0 == 2) {
            xp = xp+512;
        }
        // in der ersten Spalte, zweiten Zeile
        if (y1-y0 == 1) {
            yp = yp+256;
        }
        // in der ersten Spalte, zweiten Zeile
        if (y1-y0 == 2) {
            yp = yp+512;
        }
        // Wir fuegen dann die berechneten xp und yp in Vektor "pixelCoord" hinzu
        pixelCoord.push_back(QPointF(xp, yp));
        // wenn die Markierung nicht innerhalb die aktuellen 9 Tiles sind
        if(x1-x0 > 2 || x1-x0 < 0 || y1-y0 > 2 || y1-y0 < 0) {
            pixelCoord.pop_back();
        }
    }
}

/*Die Funktion (redrawTile) verarbeitet die Antwort auf eine Netzwerkanfrage,
die von "QNetworkReply *networkReply" repräsentiert wird.*/
void MainWindow::redrawTile(QNetworkReply *networkReply) {
    int id = networkReplyHash.value(networkReply);
    /* Das dient dazu, eine Nachricht in die Konsole auszugeben, die angibt,
    dass die Anfrage abgeschlossen ist und der Fehlercode,
    der mit der Anfrage verbunden ist*/
    cout<<"Request "<<id<<" finished with "<<networkReply->error()<<endl;

    /* Das liest alle Daten aus der Netzwerkantwort und speichert sie in
    einem QByteArray-Objekt mit dem Namen "bytes".*/
    QByteArray bytes=networkReply->readAll();
    // ein neues QPixmap-Objekt mit dem Namen "myMap".
    QPixmap myMap;
    /* Das laedt die Daten aus dem "bytes" QByteArray-Objekt in das "myMap"
    QPixmap-Objekt, wodurch ein Bild aus den Daten erstellt wird.*/
    myMap.loadFromData(bytes);
    /* Das erstellt ein neues QGraphicsPixmapItem-Objekt, "itemPtr", und fuegt
    es dem "myScene" QGraphicsScene-Objekt hinzu,
    indem das "myMap" QPixmap-Objekt als Bild verwendet wird.*/
    QGraphicsPixmapItem *itemPtr=myScene.addPixmap(myMap);

    /* x ist kleiner als 3, wenn dies der Fall ist,
    wird das Bild an der Position "x*256,0" auf der x,y-Koordinate platziert.
    Wenn x kleiner als 6 und grosser als 2 ist,
    wird das Bild an der Position "(x-3)*256,256" platziert.
    andernfalls wird das Bild an der Position "(x-6)*256,512" platziert*/
    int x = id % 3;
    int y = id / 3;
    itemPtr->setPos(x * 256, y * 256);
    /* Das wird verwendet, um die Netzwerkantwort aus dem Speicher zu entfernen,
    wenn sie nicht mehr benoetigt wird*/
    networkReply->deleteLater();

    /*Nachdem die 9 Tiles auf GraphicsView geladen wurden und "openGtxtFile"
    true ist, faengt das Programm an den Weg darauf zu zeichnen.*/
    if(myScene.items().count() == 9 && openGtxtFile){
        // "routeColor" wird erstellt, um jeden Weg eine eigene Farbe zu haben
        int routeColor = 0;
        int zoom = ui->zoomlevelLabel->text().toInt();
        // "ui->TeamNrBox->count()" ist Anzahl der Teams in einem Spieltag (3)
        // "ui->TeamNrBox->currentText()" ist das ausgewaehlte Team
        // "ui->TeamNrBox->itemText()" ist das nicht ausgewaehlte Team
        for (int j = 0; j < ui->TeamNrBox->count(); j++) {
            // um keinen Weg bei dem gleichen Ort zeichnen
            if (ui->TeamNrBox->currentText() != ui->TeamNrBox->itemText(j)) {
                /*"route" wird aufgerufen, um die Route zwischen dem aktuellen
                Team und dem Team in der Schleife zu berechnen.*/
                route(ui->TeamNrBox->currentText(), ui->TeamNrBox->itemText(j),
                      zoom);

                for (int i = 0; i < pixelCoord.size()-1; i++) {
                    /* "color" hat die Farbe schwarz wenn "routeColor" 1 ist sonst blau.
                    Der erste gezeichnete Weg ist schwarz.*/
                    QColor color = (routeColor == 1) ? Qt::black : Qt::blue;
                    /*Linien auf einer Grafik zeichnen,
                    die die berechnete Route darstellen.*/
                    QGraphicsLineItem *line = new QGraphicsLineItem
                            (pixelCoord[i].x(),pixelCoord[i].y(),
                             pixelCoord[i+1].x(),pixelCoord[i+1].y());

                    // Die Groesse der Linie ist 2 und hat die Farbe "color"
                    line->setPen(QPen(color, 2));
                    // Das Element "line" wird zu der Grafik hinzugefuegt
                    myScene.addItem(line);
                }
                //"routeColor" erhoehen, um andere Farbe von der Route zu bekommen
                routeColor++;
            }
        }
    }
}

/* Die Funktion (osmTiles) wird verwendet,
um Kacheln von einer OpenStreetMap-Server zu laden und anzuzeigen.
Der Parameter "z" gibt die Zoom-Stufe an, während die Parameter
"tileX" und "tileY" die X- und Y-Position der Kacheln im Kachel-System von
OpenStreetMap angeben. Innerhalb der Methode werden mehrere Netzwerkanfragen
erstellt und gesendet, um Kacheln an dieser Position und Zoom-Stufe zu erhalten.
Die empfangenen Kacheln werden dann in einer Szene angezeigt.*/
void MainWindow::osmTiles(int z, int tileX, int tileY) {
    /* Dies loescht alle Elemente aus der "myScene",
    um sie fuer neue Elemente vorzubereiten.*/
    myScene.clear();
    /* Beginn einer Schleife, die 3 Mal durchlaufen wird. Der Zaehler "i"
    wird hierbei verwendet, um die y-Position der Kacheln zu bestimmen.*/
    for (int i = 0; i<3; i++) {
        /* Eine weitere Schleife, die 3 Mal durchlaufen wird und
        die x-Position der Kacheln bestimmt.*/
        for (int j = 0; j<3; j++) {
            /* Dies berechnet die Position der aktuellen Kachel im Array
            "request" basierend auf den aktuellen Werten von i und j.*/
            int xy = i * 3 + j;
            /* Dies erstellt ein Object vom Typ "QNetworkRequest",
            welches zur Aufnahme der Netzwerkanfragen verwendet wird.*/
            QNetworkRequest request;
            /* Dies setzt die URL der aktuellen Kachel im Array "request"
            basierend auf den aktuellen Werten von i, j, z, tileX und tileY
            zusammen und uebergibt diese an die Methode setUrl().*/
            request.setUrl(QUrl("https://humboldt.openstreetmap.de/"+
                                 QString::number(z)+"/"+
                                 QString::number(tileX+j-1)+"/"+
                                 QString::number(tileY+i-1)+".png"));

            //erste Tile von x und y der Karte
            x0 = tileX-1;
            y0 = tileY-1;

            /* Zeiger auf QNetworkReply-Klasse. QNetworkReply bietet eine
            Moeglichkeit, auf die von einer Netzwerkanfrage zuroeckgegebenen
            Daten zuzugreifen.
            Dies sendet die aktuelle Anfrage "request" an den Netzwerkmanager
            und speichert die Antwort in "networkReply".*/
            QNetworkReply *networkReply = manager->get(request);
            /*ein neues Element in eine Hash-Tabelle mit dem Namen
            "networkReplyHash" einfuegen. Hier wird ein QNetworkReply-Objekt
            (networkReply) als Schlüssel und einen Integer-Wert (xy) als Wert
            verwendet. Der Befehl stellt also eine Verbindung zwischen dem
            QNetworkReply-Objekt und dem Integer-Wert her und speichert sie
            in der Hash-Tabelle.*/
            networkReplyHash.insert(networkReply, xy);
        }
    }
    /* Dies gibt eine Meldung auf der Konsole aus,
    dass die Anfragen gestartet wurden.*/
    cout<<"Requests started"<<endl;
    // Dies weist die "myScene" dem "graphicsView" zu.
    ui->graphicsView->setScene(&myScene);
    // Dies zeigt den "graphicsView" an.
    ui->graphicsView->show();
}

/* Die Funktion (on_mapButton_clicked) wird verwendet,
um der Button (Karte Zeigen) einzustellen,
und entscheiden was er machen muss, wenn er geklickt wird.*/
void MainWindow::on_mapButton_clicked() {
    /* eine Variable "teamNr" erstellen und mit dem Text des "TeamNrBox" aus
    der Benutzeroberflaeche gefuellt*/
    QString teamNr;
    teamNr = ui->TeamNrBox->currentText();
    // Wenn nicht, wird eine Fehlermeldung angezeigt
    if (!checkTeamNrExists(tableName, teamNr)) {
        QMessageBox::critical(this,"Fehler", "Die Teamnummer existiert nicht!");
    }
    /* Wenn die Teamnummer existiert, werden zwei Abfragen vorbereitet,
    um die Laengen- und Breitengradwerte der Spieleorte aus der Tabelle zu holen,
    die mit der angegebenen Teamnummer uebereinstimmen.
    Dann werden die Werte aus der Datenbank gelesen und in die Variablen
    "longValue" und "latValue" gespeichert.*/
    else {
        /*Die Graphinformationen aus dem gtxt-File lesen und
        den Dijkstra-Algorithmus initialisieren*/
        if (!openGtxtFile) {
            /*Die Methode "QFileDialog::getOpenFileName" oeffnet einen
            Dateidialog zur Auswahl einer Datei zum Oeffnen.*/
            /*"this" gibt an, dass das Elternfenster des Dateidialogs das
            aktuelle Fenster der Anwendung ist.
            "Kartendatei öffnen": Dies ist der Titel des Dialogs.
            "/home": Dies ist das Verzeichnis, in dem der Dialog
                    standardmaeßig geoeffnet werden soll.
            "(*.gtxt)": Dies ist ein Filter fuer die angezeigten Dateitypen
                        im Dialog. In diesem Fall werden nur Dateien mit der
                        Endung .gtxt angezeigt.*/
            gtxtFile = QFileDialog::getOpenFileName(this, "Kartendatei öffnen",
                                                    "/home", "(*.gtxt)");
            // wenn "gtxtFile" geoeffnet wurde
            if (!gtxtFile.isEmpty()) {
                d = new Dijkstra(gtxtFile.toStdString());
                openGtxtFile = true;
            }
            // wenn "gtxtFile" nicht geoeffnet wurde
            else {
                QMessageBox::critical(this,"Fehler", "Die Kartendatei (.gtxt) für "
                                                     "Route zeichnen konnte nicht "
                                                     "geöffnet werden!");
            }
        }
        /* Die x- und y-Position der Kacheln basierend auf den Werten von
        Laengen- und Breitengrad, sowie dem Zoomlevel
        ( welcher aus der Benutzeroberflaeche ausgelesen wird) berechnen.*/
        int zoom = ui->zoomlevelLabel->text().toInt();

        longTile = teamCoordLon(teamNr);
        latTile = teamCoordLat(teamNr);
        xTile = x2Tile(longTile,zoom);
        yTile = y2Tile(latTile,zoom);

        /* Die Methode "osmTiles" wird aufgerufen,
        um die Kacheln zu laden und anzuzeigen.*/
        osmTiles(zoom, xTile, yTile);
    }
}

/*Die Funktion (on_helpKarteButton_clicked) wird verwendet,
um der Button (Hilfe) einzustellen, und entscheiden was er machen muss,
wenn er geklickt wird.*/
void MainWindow::on_helpKarteButton_clicked() {
    // Hilfe-Button wird verwendet, Um Hinweise zur Bedinung zu bekommen
    QMessageBox::information(this,"Information",
                             "Klicken Sie auf den Button (Karte Zeigen), um die "
                             "Karte nach Wahl des Speiltags & Heimteams zu updaten.");
}

/* Die Funktion (on_zoomSlider_valueChanged) wird aufgerufen,
wenn der Benutzer den Zoomregler in der Benutzeroberfläche veraendert
und nich losslaesst.
Der Wert des Zoomreglers wird als Parameter "value" uebergeben.*/
void MainWindow::on_zoomSlider_valueChanged(int value) {
    /* Der aktuelle Zoomlevel auf dem "zoomlevelLabel"
    in der Benutzeroberflaeche aktualisieren.*/
    ui->zoomlevelLabel->setText(QString::number(value));
}

/* Die Funktion (on_zoomSlider_sliderReleased) wird aufgerufen,
wenn der Benutzer den Zoomregler in der Benutzeroberfläche veraendert
und losslaesst.*/
void MainWindow::on_zoomSlider_sliderReleased() {
    int zoom = ui->zoomlevelLabel->text().toInt();
    /* Wenn die Teamnummer im Eingabefeld "TeamNrBox" in der Tabelle "tableName"
    vorhanden ist*/
    if (checkTeamNrExists(tableName, ui->TeamNrBox->currentText())) {
        // Die x- und y-Position der Kacheln werden neu berechnet
        xTile = x2Tile(longTile, zoom);
        yTile = y2Tile(latTile, zoom);
        /* Die Methode "osmTiles" wird aufgerufen,
        um die Kacheln an der neu berechneten Position zu laden und anzuzeigen*/
        osmTiles(zoom, xTile, yTile);
    }
}

/* Die Funktion (on_upButton_clicked) wird verwendet,
um der Button (hoch) einzustellen,
und entscheiden was er machen muss, wenn er geklickt wird.*/
void MainWindow::on_upButton_clicked() {
    /* Wenn die Teamnummer im Eingabefeld "TeamNrBox" in der Tabelle "tableName"
    vorhanden ist*/
    if (checkTeamNrExists(tableName, ui->TeamNrBox->currentText())) {
        /* Der aktuelle Zoomlevel wird aus dem "zoomlevelLabel" in der
        Benutzeroberflaeche abgerufen und in eine Integer-Variable
        "zoom" gespeichert.*/
        int zoom = ui->zoomlevelLabel->text().toInt();
        /* Die Methode "osmTiles" wird aufgerufen, um die Kacheln eine Position
        nach oben (yTile-1) zu verschieben und anzuzeigen*/
        osmTiles(zoom, xTile, yTile-1);
        /* Die Variable "yTile" wird dann um 1 reduziert,
        um die neue y-Position der Kacheln zu speichern.*/
        yTile = yTile-1;
        /* Die Variable "longTile" und "latTile" werden dann erneut berechnet
        anhand der neuen xTile und yTile und entsprechend Zoomlevel*/
        longTile = long2Tile(xTile, zoom);
        latTile = lat2Tile(yTile, zoom);
    }
}

/* Die Funktion (on_downButton_clicked) wird verwendet,
um der Button (runter) einzustellen,
und entscheiden was er machen muss, wenn er geklickt wird.*/
void MainWindow::on_downButton_clicked() {
    /* Wenn die Teamnummer im Eingabefeld "TeamNrBox" in der Tabelle "tableName"
    vorhanden ist*/
    if (checkTeamNrExists(tableName, ui->TeamNrBox->currentText())) {
        /* Der aktuelle Zoomlevel wird aus dem "zoomlevelLabel" in der
        Benutzeroberflaeche abgerufen und in eine Integer-Variable
        "zoom" gespeichert.*/
        int zoom = ui->zoomlevelLabel->text().toInt();
        /* Die Methode "osmTiles" wird aufgerufen, um die Kacheln eine Position
        nach runter (yTile+1) zu verschieben und anzuzeigen*/
        osmTiles(zoom, xTile, yTile+1);
        /* Die Variable "yTile" wird dann um 1 erhoeht,
        um die neue y-Position der Kacheln zu speichern.*/
        yTile = yTile+1;
        /* Die Variable "longTile" und "latTile" werden dann erneut berechnet
        anhand der neuen xTile und yTile und entsprechend Zoomlevel*/
        longTile = long2Tile(xTile, zoom);
        latTile = lat2Tile(yTile, zoom);
    }
}

/* Die Funktion (on_rightButton_clicked) wird verwendet,
um der Button (rechts) einzustellen,
und entscheiden was er machen muss, wenn er geklickt wird.*/
void MainWindow::on_rightButton_clicked() {
    /* Wenn die Teamnummer im Eingabefeld "TeamNrBox" in der Tabelle "tableName"
    vorhanden ist*/
    if (checkTeamNrExists(tableName, ui->TeamNrBox->currentText())) {
        /* Der aktuelle Zoomlevel wird aus dem "zoomlevelLabel" in der
        Benutzeroberflaeche abgerufen und in eine Integer-Variable
        "zoom" gespeichert.*/
        int zoom = ui->zoomlevelLabel->text().toInt();
        /* Die Methode "osmTiles" wird aufgerufen, um die Kacheln eine Position
        nach rechts (xTile+1) zu verschieben und anzuzeigen*/
        osmTiles(zoom, xTile+1, yTile);
        /* Die Variable "xTile" wird dann um 1 erhoeht,
        um die neue x-Position der Kacheln zu speichern.*/
        xTile = xTile+1;
        /* Die Variable "longTile" und "latTile" werden dann erneut berechnet
        anhand der neuen xTile und yTile und entsprechend Zoomlevel*/
        longTile = long2Tile(xTile, zoom);
        latTile = lat2Tile(yTile, zoom);
    }
}

/* Die Funktion (on_leftButton_clicked) wird verwendet,
um der Button (links) einzustellen,
und entscheiden was er machen muss, wenn er geklickt wird.*/
void MainWindow::on_leftButton_clicked() {
    /* Wenn die Teamnummer im Eingabefeld "TeamNrBox" in der Tabelle "tableName"
    vorhanden ist*/
    if (checkTeamNrExists(tableName, ui->TeamNrBox->currentText())) {
        /* Der aktuelle Zoomlevel wird aus dem "zoomlevelLabel" in der
        Benutzeroberflaeche abgerufen und in eine Integer-Variable
        "zoom" gespeichert.*/
        int zoom = ui->zoomlevelLabel->text().toInt();
        /* Die Methode "osmTiles" wird aufgerufen, um die Kacheln eine Position
        nach links (xTile-1) zu verschieben und anzuzeigen*/
        osmTiles(zoom, xTile-1, yTile);
        /* Die Variable "xTile" wird dann um 1 reduziert,
        um die neue x-Position der Kacheln zu speichern.*/
        xTile = xTile-1;
        /* Die Variable "longTile" und "latTile" werden dann erneut berechnet
        anhand der neuen xTile und yTile und entsprechend Zoomlevel*/
        longTile = long2Tile(xTile, zoom);
        latTile = lat2Tile(yTile, zoom);
    }
}
