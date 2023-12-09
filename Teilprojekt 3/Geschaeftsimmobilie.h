/***********************************************

Geschaeftsimmobilie.h - Header-File von Geschaeftsimmobilie.cpp

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 28.11.2022

***********************************************/
#include "Immobilie.h"

#ifndef GESCHAEFTSIMMOBILIE_H    //  Wenn die Datei schon definiert wurde, dann überspringt alles und geht zum Ende #endif, sonst definieren und kompilieren
#define GESCHAEFTSIMMOBILIE_H    //  Die Datei definieren und kompilieren

class Geschaeftsimmobilie : public Immobilie {
        //      Die Klasse Geschaeftsimmobilie
        private:
                std::string also_apartment;
        
        public:
                Geschaeftsimmobilie(); 
                ~Geschaeftsimmobilie() override;
                void eingabe() override; 
                void ausgabe(std::fstream& outputFile) override;
};
#endif