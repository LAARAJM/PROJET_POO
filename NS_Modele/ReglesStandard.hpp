#pragma once

#include "Regle.hpp"
#include "CelluleVivante.hpp"
#include "CelluleMorte.hpp"


namespace NS_Modele { //Namespace du modèle

    class ReglesStandard : public Regle { //La classe Regle Standard hérite de la classe abstraite Regle
    public:

        ReglesStandard() = default; //Constructeur par défaut

        virtual ~ReglesStandard() = default; //Destructeur virtuel par défaut

        //Determine le prochain état d'une cellule
        virtual Cellule* obtenirNouvelEtat(Cellule* celluleActuelle, int nbVoisinsVivants) override; //Cellule courante et nombre de voisins vivants
        
    };
}