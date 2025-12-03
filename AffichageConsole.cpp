#include "AffichageConsole.hpp"
#include "Grille.hpp"
#include "Cellule.hpp"
#include <iostream>

namespace NS_Vue {

    AffichageConsole::AffichageConsole() : numeroIteration(0) {}

    void AffichageConsole::initialiser() {
        std::cout << "Jeu de la Vie - Mode Console" << std::endl;
        std::cout << std::endl;
    }

    void AffichageConsole::afficher(NS_Modele::Grille* grille, int n) {
        numeroIteration = n;
        
        std::cout << "Iteration " << numeroIteration << " :" << std::endl;
        
        int hauteur = grille->getHauteur();
        int largeur = grille->getLargeur();
        
        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < largeur; j++) {
                NS_Modele::Cellule* cellule = grille->obtenirCellule(j, i);
                if (cellule) {
                    std::cout << cellule->getSymbole();
                } else {
                    std::cout << '?'; // Indicateur d'erreur
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void AffichageConsole::nettoyer() {
        std::cout << "Fin de la simulation" << std::endl;
    }

    void AffichageConsole::afficherMessage(const std::string& message) {
        std::cout << message << std::endl;
    }

}