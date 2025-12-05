#pragma once

#include <string>
#include "Affichage.hpp"

namespace NS_Modele { //Namespace du modèle
    class Grille; //Déclaration de la classe Grille
}

namespace NS_Vue { //Namespace de la vue

    class AffichageConsole : public Affichage { //La classe Affichage Console hérite de la classe abstraite Affichage
    private:
        int numeroIteration; //Numéro de l'itération affichée

    public:

        AffichageConsole(); //Constructeur


        void initialiser() override; //Initialise l'affichage console

        void afficher(NS_Modele::Grille* grille, int n) override; //Affiche la grille à l'itération

 
        void nettoyer() override; //Nettoyage de l'affichage 

  
        void afficherMessage(const std::string& message) override; //Affiche une message d'information
    };

}
