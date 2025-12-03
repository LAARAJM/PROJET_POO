#include "GestionFichier.hpp"
#include "CelluleVivante.hpp"
#include "CelluleMorte.hpp"
#include "CelluleObstacle.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace Controleur {

NS_Modele::Grille* GestionFichier::chargerGrille(const std::string& cheminFichier) {
    std::ifstream fichier(cheminFichier);
    
    if (!fichier.is_open()) {
        afficherErreur("Impossible d'ouvrir le fichier: " + cheminFichier);
        return nullptr;
    }

    try {
        std::string premiereLigne;
        std::getline(fichier, premiereLigne);
        
        std::istringstream iss(premiereLigne);
        int largeur, hauteur;
        char modeTorique = 'F';
        
        iss >> largeur >> hauteur;
        
        // Vérifier si un mode torique est spécifié
        if (iss >> modeTorique) {
            modeTorique = std::toupper(modeTorique);
        }
        
        if (largeur <= 0 || hauteur <= 0) {
            afficherErreur("Dimensions invalides dans le fichier");
            return nullptr;
        }

        bool torique = (modeTorique == 'T');
        NS_Modele::Grille* grille = new NS_Modele::Grille(largeur, hauteur, torique);

        // Lecture de la grille ligne par ligne
        std::vector<std::string> lignes;
        std::string ligne;
        
        while (std::getline(fichier, ligne) && lignes.size() < static_cast<size_t>(hauteur)) {
            if (!ligne.empty()) {
                lignes.push_back(ligne);
            }
        }

        if (lignes.size() != static_cast<size_t>(hauteur)) {
            afficherErreur("Nombre de lignes incorrect dans le fichier");
            delete grille;
            return nullptr;
        }

        // Remplissage de la grille
        for (int y = 0; y < hauteur; ++y) {
            for (int x = 0; x < largeur && x < static_cast<int>(lignes[y].length()); ++x) {
                char c = lignes[y][x];
                NS_Modele::Cellule* cellule = nullptr;

                switch (c) {
                    case '1':
                    case 'O':
                    case 'o':
                        cellule = new NS_Modele::CelluleVivante();
                        break;
                    case '0':
                    case '.':
                    case ' ':
                        cellule = new NS_Modele::CelluleMorte();
                        break;
                    case 'X':
                    case 'x':
                        cellule = new NS_Modele::CelluleObstacle(true);
                        break;
                    default:
                        cellule = new NS_Modele::CelluleMorte();
                        break;
                }

                grille->definirCellule(x, y, cellule);
            }
            
            // Remplir les cellules manquantes avec des cellules mortes
            for (int x = lignes[y].length(); x < largeur; ++x) {
                grille->definirCellule(x, y, new NS_Modele::CelluleMorte());
            }
        }

        fichier.close();
        std::cout << "[INFO] Grille chargée avec succès: " << largeur << "x" << hauteur 
                  << (torique ? " (mode torique)" : " (mode non-torique)") << std::endl;
        
        return grille;

    } catch (const std::exception& e) {
        afficherErreur("Erreur lors du chargement: " + std::string(e.what()));
        fichier.close();
        return nullptr;
    }
}

void GestionFichier::sauvegarderGrille(const std::string& cheminFichier, 
                                       const NS_Modele::Grille* grille, 
                                       int iteration) {
    if (!grille) {
        afficherErreur("Grille invalide pour la sauvegarde");
        return;
    }

    std::ofstream fichier(cheminFichier);
    
    if (!fichier.is_open()) {
        afficherErreur("Impossible de créer le fichier: " + cheminFichier);
        return;
    }

    try {
        
        fichier << grille->getLargeur() << " " << grille->getHauteur();
        if (grille->getModeTorique()) {
            fichier << " T";
        }
        fichier << std::endl;

       
        fichier << "# Itération: " << iteration << std::endl;

        
        for (int y = 0; y < grille->getHauteur(); ++y) {
            for (int x = 0; x < grille->getLargeur(); ++x) {
                const NS_Modele::Cellule* cellule = grille->obtenirCellule(x, y);
                fichier << cellule->getSymbole();
            }
            fichier << std::endl;
        }

        fichier.close();
        std::cout << "[INFO] Grille sauvegardée dans: " << cheminFichier << std::endl;

    } catch (const std::exception& e) {
        afficherErreur("Erreur lors de la sauvegarde: " + std::string(e.what()));
        fichier.close();
    }
}

bool GestionFichier::validerFormat(const std::string& cheminFichier) {
    if (!fichierExiste(cheminFichier)) {
        return false;
    }

    std::ifstream fichier(cheminFichier);
    
    if (!fichier.is_open()) {
        return false;
    }

    try {
        std::string premiereLigne;
        std::getline(fichier, premiereLigne);
        
        std::istringstream iss(premiereLigne);
        int largeur, hauteur;
        
        if (!(iss >> largeur >> hauteur)) {
            fichier.close();
            return false;
        }

        if (largeur <= 0 || hauteur <= 0 || largeur > 1000 || hauteur > 1000) {
            fichier.close();
            return false;
        }

        
        int compteurLignes = 0;
        std::string ligne;
        
        while (std::getline(fichier, ligne) && compteurLignes < hauteur) {
            if (!ligne.empty() && ligne[0] != '#') {
                compteurLignes++;
            }
        }

        fichier.close();
        return compteurLignes == hauteur;

    } catch (const std::exception&) {
        fichier.close();
        return false;
    }
}

bool GestionFichier::fichierExiste(const std::string& chemin) {
    std::ifstream fichier(chemin);
    bool existe = fichier.good();
    fichier.close();
    return existe;
}

void GestionFichier::afficherErreur(const std::string& message) {
    std::cerr << "[ERREUR] " << message << std::endl;
}

} 
