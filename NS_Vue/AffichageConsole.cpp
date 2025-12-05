#include "AffichageConsole.hpp"
#include "Grille.hpp"
#include "Cellule.hpp"
#include <iostream>

namespace NS_Vue { //Namespace de la vue

    AffichageConsole::AffichageConsole() : numeroIteration(0) {} //Constructeur qui initialise l'itération à 0

    void AffichageConsole::initialiser() { //Initialise l'affichage console
        std::cout << "Jeu de la Vie - Mode Console" << std::endl; //Message d'en tête
        std::cout << std::endl; //Ligne vide
    }

    void AffichageConsole::afficher(NS_Modele::Grille* grille, int n) { //Affiche la grille à l'itération
        numeroIteration = n; //Met à jour l'itération courante
        
        std::cout << "Iteration " << numeroIteration << " :" << std::endl; //Affiche le numéro d'itération
        
        int hauteur = grille->getHauteur(); //Récupère la hauteur de la grille
        int largeur = grille->getLargeur(); //Récupère la largeur de la grille
        
        for (int i = 0; i < hauteur; i++) { //Parcourt chaque ligne
            for (int j = 0; j < largeur; j++) { //Parcourt chaque colonne
                NS_Modele::Cellule* cellule = grille->obtenirCellule(j, i); //Récupère la cellule
                if (cellule) { //Si la cellule existe
                    std::cout << cellule->getSymbole(); //Affiche son symbole
                } else {
                    std::cout << '?'; //Si problème -> affiche un caractère inconnu
                }
            }
            std::cout << std::endl; //Fin de ligne
        }
        std::cout << std::endl; //Ligne vide après la grille
    }

    void AffichageConsole::nettoyer() { //Nettoyage de l'affichage
        std::cout << "Fin de la simulation" << std::endl;
    }

    void AffichageConsole::afficherMessage(const std::string& message) { //Affiche un message d'information
        std::cout << message << std::endl;
    }

}