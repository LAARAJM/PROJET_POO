#include "Jeu.hpp"
#include "Grille.hpp"
#include "Regle.hpp"
#include "Affichage.hpp"
#include "AffichageGraphique.hpp"
#include "GestionFichier.hpp"
#include <iostream>

namespace NS_Controleur {

    Jeu::Jeu(NS_Modele::Grille* g, NS_Modele::Regle* r, NS_Vue::Affichage* a, int nbIterations)
        : grille(g), regle(r), affichage(a), iterationCourante(0), iterationsMax(nbIterations) {}

    Jeu::~Jeu() {
        delete grille;
        delete regle;
        delete affichage;
        
        // Nettoyer l'historique
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
        
        // Messages de fin
        if (iterationCourante >= iterationsMax) {
            affichage->afficherMessage("Limite d'iterations atteinte : " + std::to_string(iterationsMax));
        } else if (estStable()) {
            affichage->afficherMessage("Grille stabilisee - Aucune evolution");
        }
        
        affichage->nettoyer();
    }

    void Jeu::etape() {
        // Sauvegarder l'état actuel
        grillesPrecedentes.push_back(grille->clone());
        
        // Mettre à jour la grille
        grille->mettreAJour(regle);
        
        iterationCourante++;

        // Sauvegarder l'itération
        sauvegarderIterationCourante();
        
        // Afficher
        affichage->afficher(grille, iterationCourante);
    }

    bool Jeu::doitArreter() {
        // Vérifier si c'est un affichage graphique et si la fenêtre est fermée
        NS_Vue::AffichageGraphique* affichageGraph = 
            dynamic_cast<NS_Vue::AffichageGraphique*>(affichage);
        
        if (affichageGraph && affichageGraph->estFermee()) {
            std::cout << "[INFO] Arrêt demandé par l'utilisateur" << std::endl;
            return true;
        }
        
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
        
        // Comparer avec la grille précédente
        NS_Modele::Grille* derniere = grillesPrecedentes.back();
        
        return grille->estIdentique(derniere);
    }

    int Jeu::getIteration() const {
        return iterationCourante;
    }

    void Jeu::sauvegarderIterationCourante() {
        std::string nomFichier = "jeu_de_la_vie/grille_" + std::to_string(iterationCourante) + ".txt";
        GestionFichier::sauvegarderGrille(nomFichier, grille, iterationCourante);
    }

}