#pragma once
#include "Cellule.hpp" 

namespace NS_Modele { //Namespace du modèle

    class Regle { //Déclaration de la classe abstraite Regle
    public:

        //Calcule le nouvel état d'une cellule
        virtual Cellule* obtenirNouvelEtat(Cellule* celluleActuelle, int nbVoisinsVivants) = 0; //Cellule à analyser et nombre de voisins vivants

        virtual ~Regle() = default; //Destructeur virtuel par défaut
        
    };
}