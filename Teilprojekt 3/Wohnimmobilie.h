/***********************************************

Wohnimmobilie.h - Header-File von Wohnimmobilie.cpp

Autor: Amgad Alghabra

Kontakt: amgad.alghabra1996@gmail.com

Letzte Bearbeitung am: 28.11.2022

***********************************************/
#include "Immobilie.h"

#ifndef WOHNIMMOBILIE_H    //  Wenn die Datei schon definiert wurde, dann überspringt alles und geht zum Ende #endif, sonst definieren und kompilieren
#define WOHNIMMOBILIE_H    //  Die Datei definieren und kompilieren

class Wohnimmobilie : public Immobilie {
        //      Die Klasse Wohnimmobilie
        private:
                std::string apartment_or_house;
                
        public:
                Wohnimmobilie();
                ~Wohnimmobilie() override; 
                void eingabe() override;
                void ausgabe(std::fstream& outputFile) override;
};
#endif