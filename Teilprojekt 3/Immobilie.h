/***********************************************

Immobilie.h - Header-File von Immobilie.cpp

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 28.11.2022

***********************************************/

#ifndef IMMOBILIE_H    //  Wenn die Datei schon definiert wurde, dann überspringt alles und geht zum Ende #endif, sonst definieren und kompilieren
#define IMMOBILIE_H    //  Die Datei definieren und kompilieren

class Immobilie {
        //      Die Klasse Immobilie
        private:
                std::string adresse;
                std::string baujahr;
                std::string besitzer;
        
        public:
                Immobilie(); 
                virtual ~Immobilie();
                virtual void eingabe(); 
                virtual void ausgabe(std::fstream& outputFile);
};
#endif