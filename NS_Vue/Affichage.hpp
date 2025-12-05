#pragma once

#include <string>

namespace NS_Modele { //Namespace du modèle
    class Grille; //Déclaration de la classe Grille
}

namespace NS_Vue { //Namespace de la vue
    class Affichage { //Déclaration de la classe Affichage
    public:
        virtual ~Affichage() = default; //Destructeur virtual par défaut

        virtual void initialiser() = 0; //Initialise l'affichage 

        virtual void afficher(NS_Modele::Grille* grille, int n) = 0; //Affiche une grille à l'itération

        virtual void nettoyer() = 0; //Nettoie l'affichage

        virtual void afficherMessage(const std::string& message) = 0; //Affiche un message d'information
    };

}
