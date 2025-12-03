#include "Jeu.hpp"
#include "Grille.hpp"
#include "Regle.hpp"
#include "Affichage.hpp"
#include "GestionFichier.hpp"
#include <iostream>

namespace NS_Controleur {

    Jeu::Jeu(NS_Modele::Grille* g, NS_Modele::Regle* r, NS_Vue::Affichage* a, int nbIterations)
        : grille(g), regle(r), affichage(a), iterationCourante(0), iterationsMax(nbIterations) {}

    Jeu::~Jeu() {
        delete grille;
        delete regle;
        delete affichage;
        

        for (NS_Modele::Grille* g : grillesPrecedentes) {
            delete g;
        }
    }

    void Jeu::initialiser() {
        affichage->initialiser();
        affichage->afficher(grille, 0);
    }

    void Jeu::executer() {
        while (!doitArreter()) {
            etape();
        }
        

        if (iterationCourante >= iterationsMax) {
            affichage->afficherMessage("Limite d'iterations atteinte : " + std::to_string(iterationsMax));
        } else if (estStable()) {
            affichage->afficherMessage("Grille stabilisee - Aucune evolution");
        }
        
        affichage->nettoyer();
    }

    void Jeu::etape() {
        grillesPrecedentes.push_back(grille->clone());
        
        grille->mettreAJour(regle);
        
        iterationCourante++;

        sauvegarderIterationCourante();
        
        affichage->afficher(grille, iterationCourante);
    }

    bool Jeu::doitArreter() {
        if (iterationCourante >= iterationsMax) {
            return true;
        }
        
        if (estStable()) {
            return true;
        }
        
        return false;
    }

    bool Jeu::estStable() {
        if (grillesPrecedentes.empty()) {
            return false;
        }
        

        NS_Modele::Grille* derniere = grillesPrecedentes.back();
        
        int hauteur = grille->getHauteur();
        int largeur = grille->getLargeur();
        
        for (int i = 0; i < hauteur; i++) {
            for (int j = 0; j < largeur; j++) {
                if (grille->obtenirCellule(i, j)->getSymbole() != 
                    derniere->obtenirCellule(i, j)->getSymbole()) {
                    return false;
                }
            }
        }
        
        return true;
    }

    int Jeu::getIteration() const {
        return iterationCourante;
    }

    void Jeu::sauvegarderIterationCourante() {
        std::string nomFichier = "jeu_de_la_vie/grille_" + std::to_string(iterationCourante) + ".txt";
        GestionFichier::sauvegarderGrille(nomFichier, grille, iterationCourante);
    }

}