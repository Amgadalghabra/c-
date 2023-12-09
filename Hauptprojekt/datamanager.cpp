/***********************************************

datamanager.cpp

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 11.01.2023

***********************************************/

#include "datamanager.h"

DataManager::DataManager() {} //  Konstruktor
DataManager::~DataManager() {}    //  Destruktor

// Die Funktion (createDatabase) wird verwendet, um eine Datenbank zu erstellen.
void DataManager::createDatabase(QString dbName) {
    /*QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); ist eine Anweisung,
    die eine neue Instanz der QSqlDatabase-Klasse mit dem Namen "db" erstellt
    und die Datenbankverbindung für eine SQLite-Datenbank festlegt.*/
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    /*Die setDatabaseName()-Methode wird dann verwendet,
    um den Namen der Datenbank festzulegen.
    "dbName"-Variable enthaelt der Name.*/
    db.setDatabaseName(dbName);

    //  Wenn db nicht geoeffnet werden kann
    if(!db.open()) {
        //  dann das ausdrucken
        qWarning() << "Problem opening database!";
    }
}

/*Die Funktion (createTable) wird verwendet,
um eine Tabelle in dem Datenbank zu erstellen
und die Eingaben der Teams darin zu speichern.*/
void DataManager::createTable(QString tableName, QString columnNames) {
    /*wir erstellen eine Tabelle "tableName", wenn sie nicht existiert.
    "columnNames"-Variable enthaelt die Spaltennamen.
    Das wird in "query" gespeichert.*/
    QString query("CREATE TABLE IF NOT EXISTS "+ tableName +
                  " ("+columnNames+");");
    QSqlQuery qry;

    //  wenn das nicht geklappt hat
    if(!qry.exec(query)) {
        //  dann das ausdrucken
        qWarning() << "ERROR creating table!";
    }
}

/*Die Funktion (insertRecord) wird verwendet,
um die Daten von jedem Team in der Tabelle zu speichern.
Die Daten sind in den Variablen: number, name, location, coorGameLocationLat,
coorGameLocationLong, leader.*/
bool DataManager::insertRecord(QString tableName, QString number, QString name,
                               QString location, QString coorGameLocationLat,
                               QString coorGameLocationLong, QString leader) {
    //  Wir speichern hier die Eingaben in der Tabelle
    QSqlQuery query;
    query.prepare("INSERT INTO " + tableName + " VALUES ('"+number+"','"+name
                  +"','"+location+"','"+coorGameLocationLat+"','"
                  +coorGameLocationLong+"','"+leader+"');");

    //  wenn das geklappt hat
    if(query.exec()) {
        //  dann das ausdrucken
        qWarning() << "Saved!";
    }
    //  sonst
    else {
        qWarning() << "ERROR inserting record!";
        return false;
    }

    return true;
}

/*Die Funktion (deleteRecord) wird verwendet,
um ein Datensatz zu loeschen.*/
bool DataManager::deleteRecord(QString tableName, QString firstColumnName,
                               QString number) {
    /*Wir entfernen hier der Datensatz aus der Tabelle, wenn die Bedingung
    "number" in der ersten Spalte "firstColumnName" erfuellt ist.*/
    QSqlQuery query;
    query.prepare("DELETE from " + tableName + " WHERE "+ firstColumnName +
                  " = '"+number+"'");

    //  wenn das geklappt hat
    if(query.exec()) {
        //  dann das ausdrucken
        qWarning() << "Deleted!";
    }
    //  sonst
    else {
        qWarning() << "ERROR deleting record!";
        return false;
    }

    return true;
}

/*Die Funktion (showTable) wird verwendet, um die Datensaetze in einer
Tabelle (tableView) und die Teamsnummer in einer Liste (listView) anzuzeigen.*/
void DataManager::showTable(QString tableName, QTableView* tableView,
                            QListView* listView) {
    /*Die QSqlTableModel-Klasse ermoeglicht, Daten aus einer Datenbanktabelle
    in eine grafische Benutzeroberflaeche (GUI) einzubinden.
    "modal" ist ein Objekt. Die Tabelle wird,
    deren Inhalte angezeigt werden sollen,
    mit der Methode setTable() festgelegt.
    Die Methode select() laedt anschließend die Inhalte der Tabelle
    in das QSqlTableModel. Das QSqlTableModel wird mit der Methode setModel()
    dem QTableView-Objekt "tableView" zugewiesen.*/
    QSqlTableModel *modal = new QSqlTableModel;
    modal->setTable(tableName);
    modal->select();
    tableView->setModel(modal);

    /*Die Methode setModelColumn() legt fest, welche Spalte des QSqlTableModels
    im QListView angezeigt werden soll. In diesem Fall wird die erste Spalte
    (mit dem Index 0) "Teamsnummer" angezeigt.*/
    listView->setModel(modal);
    listView->setModelColumn(0);
}
