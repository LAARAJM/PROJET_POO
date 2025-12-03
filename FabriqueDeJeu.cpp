#include "FabriqueDeJeu.hpp"
#include <iostream>

// Inclusions du Contrôleur
#include "Jeu.hpp"
#include "GestionFichier.hpp" 

// Inclusions du Modèle
#include "ReglesStandard.hpp" 
#include "Grille.hpp"

// Inclusions de la Vue
#include "AffichageConsole.hpp" 
#include "AffichageGraphique.hpp" 

// Assurez-vous que ce namespace correspond à celui utilisé dans FabriqueDeJeu.hpp et main.cpp
namespace NS_Controleur { 

    NS_Controleur::Jeu* FabriqueDeJeu::creerDepuisFichier(const std::string& fichier, 
                                                         const std::string& mode, 
                                                         int iterMax) {
        
        // --- 1. Pointeurs à construire ---
        NS_Modele::Grille* grille = nullptr;
        NS_Modele::Regle* regle = nullptr;
        NS_Vue::Affichage* affichage = nullptr; // Notez le namespace de la Vue

        // --- 2. Chargement de la Grille (via GestionFichier) ---
        
        // La validation du format est déjà faite dans main.cpp, mais la sécurité est bonne.
        // On passe directement au chargement.
        grille = GestionFichier::chargerGrille(fichier);
        
        if (grille == nullptr) {
            std::cerr << "[FABRIQUE] Erreur: Échec du chargement de la grille ou format non valide." << std::endl;
            return nullptr;
        }

        // --- 3. Création de la Règle (Standard par défaut) ---
        
        // Pour ce projet, on utilise toujours la règle standard
        regle = new NS_Modele::ReglesStandard();

        // --- 4. Création de l'Affichage (Dépend du mode) ---
        
        if (mode == "console") {
            affichage = new NS_Vue::AffichageConsole();
        } else if (mode == "graphique") {
            // Paramètres par défaut pour l'affichage graphique
            const int TAILLE_CELLULE = 20; 
            const float DELAI = 0.1f; // 100 millisecondes
            
            // Assurez-vous que le constructeur de AffichageGraphique est bien dans NS_Vue
            affichage = new NS_Vue::AffichageGraphique(TAILLE_CELLULE, DELAI);
        } else {
            // Cas inattendu (main.cpp aurait dû le bloquer)
            std::cerr << "[FABRIQUE] Erreur: Mode d'affichage inconnu : " << mode << std::endl;
            // Nettoyage avant de retourner
            delete grille; 
            delete regle;
            return nullptr;
        }

        // --- 5. Assemblage du Jeu ---
        
        // Le constructeur de Jeu prend possession de grille, regle, et affichage
        NS_Controleur::Jeu* nouveauJeu = new NS_Controleur::Jeu(grille, regle, affichage, iterMax);

        return nouveauJeu;
    }
}