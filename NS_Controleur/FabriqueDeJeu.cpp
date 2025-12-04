#include "FabriqueDeJeu.hpp"
#include <iostream>


#include "Jeu.hpp"
#include "GestionFichier.hpp" 


#include "Grille.hpp"
#include "ReglesStandard.hpp" 


#include "AffichageConsole.hpp" 
#include "AffichageGraphique.hpp" 


namespace NS_Controleur { 

    NS_Controleur::Jeu* FabriqueDeJeu::creerDepuisFichier(const std::string& fichier, 
                                                         const std::string& mode, 
                                                         int iterMax) {
        
        NS_Modele::Grille* grille = nullptr;
        NS_Modele::Regle* regle = nullptr;
        NS_Vue::Affichage* affichage = nullptr; 

        grille = GestionFichier::chargerGrille(fichier);
        
        if (grille == nullptr) {
            std::cerr << "[FABRIQUE] Erreur: Échec du chargement de la grille ou format non valide." << std::endl;
            return nullptr;
        }

        regle = new NS_Modele::ReglesStandard();
        
        if (mode == "console") {
            affichage = new NS_Vue::AffichageConsole();
        } else if (mode == "graphique") {
            const int TAILLE_CELLULE = 50; 
            const float DELAI = 0.2f; 
            affichage = new NS_Vue::AffichageGraphique(TAILLE_CELLULE, DELAI);
        } else {
            std::cerr << "[FABRIQUE] Erreur: Mode d'affichage inconnu : " << mode << std::endl;
            delete grille; 
            delete regle;
            return nullptr;
        }

        NS_Controleur::Jeu* nouveauJeu = new NS_Controleur::Jeu(grille, regle, affichage, iterMax);

        return nouveauJeu;
    }
}