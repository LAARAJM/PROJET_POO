#include "FabriqueDeJeu.hpp"
#include <iostream>


#include "Jeu.hpp"
#include "GestionFichier.hpp" 


#include "Grille.hpp"
#include "ReglesStandard.hpp" 


#include "AffichageConsole.hpp" 
#include "AffichageGraphique.hpp" 


namespace NS_Controleur {  //Début du namespace Controleur

    //Méthode créant un Jeu ) partir d'un fichier et d'un mode
    NS_Controleur::Jeu* FabriqueDeJeu::creerDepuisFichier(const std::string& fichier, 
                                                         const std::string& mode, 
                                                         int iterMax) {
        
        NS_Modele::Grille* grille = nullptr; //Pointeur vers la grille 
        NS_Modele::Regle* regle = nullptr; //Pointeur vers la règle d'évolution
        NS_Vue::Affichage* affichage = nullptr; //Pointeur vers l'affichage choisi

        grille = GestionFichier::chargerGrille(fichier); //Charger la grille depuis le fichier
        
        if (grille == nullptr) { //Vérifie si le changement a échoué 
            std::cerr << "[FABRIQUE] Erreur: Échec du chargement de la grille ou format non valide." << std::endl; //Message d'erreur
            return nullptr; //Retourne nullptr si problème
        }

        regle = new NS_Modele::ReglesStandard(); //Création de la règle standard
        
        if (mode == "console") { //Si mode console est choisi
            affichage = new NS_Vue::AffichageConsole(); //Création de l'affichage console
        } else if (mode == "graphique") { //Si mode graphique est choisi
            const int TAILLE_CELLULE = 50; //Taille des cellules graphiques
            const float DELAI = 0.2f; //Delai entre deux affichages
            affichage = new NS_Vue::AffichageGraphique(TAILLE_CELLULE, DELAI); //Affichage graphique
        } else { //Mode inconnu
            std::cerr << "[FABRIQUE] Erreur: Mode d'affichage inconnu : " << mode << std::endl; //Message d'erreur
            delete grille; //Libère la grille
            delete regle; //Libère la règle 
            return nullptr; //Retourne nullptr
        }

        NS_Controleur::Jeu* nouveauJeu = new NS_Controleur::Jeu(grille, regle, affichage, iterMax); //Créer le jeu

        return nouveauJeu; //Retourne le jeu créé
    }
}