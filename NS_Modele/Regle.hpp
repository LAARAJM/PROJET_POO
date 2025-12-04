#pragma once
#include "Cellule.hpp" 

namespace NS_Modele {

    class Regle {
    public:

        virtual Cellule* obtenirNouvelEtat(Cellule* celluleActuelle, int nbVoisinsVivants) = 0;

        virtual ~Regle() = default;
        
    };
}