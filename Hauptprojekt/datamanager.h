/***********************************************

datamanager.h - Header-File von datamanager.cpp

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 11.01.2023

***********************************************/

#ifndef DATAMANAGER_H   //  Wenn die Datei schon definiert wurde, dann ueberspringt alles und geht zum Ende #endif, sonst definieren und kompilieren
#define DATAMANAGER_H   //  Die Datei definieren und kompilieren

#include <QDialog>
#include <QTableView>
#include <QListView>
#include <QtSql>

/*DataManager wird verwendet, um eine Datenbank und eine Tabelle anzulegen,
Datensatz einzufuegen und zu loeschen,
und die Datensaetze in einer Tabelle anzuzeigen*/
class DataManager {
    public:
        DataManager();
        ~DataManager();
        void createDatabase(QString dbName);
        void createTable(QString tableName, QString columnNames);
        bool insertRecord(QString tableName, QString number, QString name,
                          QString location, QString coorGameLocationLat,
                          QString coorGameLocationLong, QString leader);
        bool deleteRecord(QString tableName, QString firstColumnName, QString number);
        void showTable(QString tableName, QTableView* tableView, QListView* listView);
};
#endif // DATAMANAGER_H
