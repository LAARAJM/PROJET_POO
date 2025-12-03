#include "GestionFichier.hpp"
#include "Grille.hpp"
#include "Cellule.hpp"
#include "CelluleVivante.hpp"
#include "CelluleMorte.hpp"
#include "CelluleObstacle.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <iomanip>

namespace NS_Controleur {

    NS_Modele::Grille* GestionFichier::chargerGrille(const std::string& cheminFichier) {
        std::ifstream fichier(cheminFichier);
        
        if (!fichier.is_open()) {
            std::cerr << "[ERREUR] Impossible d'ouvrir le fichier: " << cheminFichier << std::endl;
            return nullptr;
        }

        try {
            std::string premiereLigne;
            std::getline(fichier, premiereLigne);
            
            std::istringstream iss(premiereLigne);
            int hauteur, largeur;  // ← Corrigé : hauteur puis largeur
            char modeTorique = 'F';
            
            iss >> hauteur >> largeur;  // ← Corrigé
            
            if (iss >> modeTorique) {
                modeTorique = std::toupper(modeTorique);
            }
            
            if (largeur <= 0 || hauteur <= 0) {
                std::cerr << "[ERREUR] Dimensions invalides dans le fichier" << std::endl;
                return nullptr;
            }

            bool torique = (modeTorique == 'T');
            NS_Modele::Grille* grille = new NS_Modele::Grille(largeur, hauteur, torique);

            std::vector<std::string> lignes;
            std::string ligne;
            
            while (std::getline(fichier, ligne) && lignes.size() < static_cast<size_t>(hauteur)) {
                if (!ligne.empty() && ligne[0] != '#') {
                    lignes.push_back(ligne);
                }
            }

            if (lignes.size() != static_cast<size_t>(hauteur)) {
                std::cerr << "[ERREUR] Nombre de lignes incorrect dans le fichier" << std::endl;
                delete grille;
                return nullptr;
            }

            for (int y = 0; y < hauteur; ++y) {
                std::istringstream lineStream(lignes[y]);
                int valeur;
                int x = 0;
                
                while (lineStream >> valeur && x < largeur) {
                    NS_Modele::Cellule* cellule = nullptr;

                    switch (valeur) {
                        case 1:
                            cellule = new NS_Modele::CelluleVivante();
                            break;
                        case 2:
                            cellule = new NS_Modele::CelluleObstacle();
                            break;
                        case 0:
                        default:
                            cellule = new NS_Modele::CelluleMorte();
                            break;
                    }

                    grille->definirCellule(x, y, cellule);
                    x++;
                }
                
                // Remplir les cellules manquantes avec des cellules mortes
                for (; x < largeur; ++x) {
                    grille->definirCellule(x, y, new NS_Modele::CelluleMorte());
                }
            }

            fichier.close();
            std::cout << "[INFO] Grille chargee avec succes: " << hauteur << "x" << largeur 
                      << (torique ? " (mode torique)" : " (mode non-torique)") << std::endl;
            
            return grille;

        } catch (const std::exception& e) {
            std::cerr << "[ERREUR] Erreur lors du chargement: " << e.what() << std::endl;
            fichier.close();
            return nullptr;
        }
    }

    void GestionFichier::sauvegarderGrille(const std::string& dossierSortie,
                                           NS_Modele::Grille* grille,
                                           int iteration) {
        if (!grille) {
            std::cerr << "[ERREUR] Grille nulle" << std::endl;
            return;
        }

        // Créer le dossier s'il n'existe pas
        try {
            std::filesystem::create_directories(dossierSortie);
        } catch (const std::exception& e) {
            std::cerr << "[ERREUR] Impossible de créer le dossier : " 
                     << e.what() << std::endl;
            return;
        }

        // Nom du fichier : iteration_0001.txt
        std::ostringstream nomFichier;
        nomFichier << dossierSortie << "/iteration_" 
                  << std::setfill('0') << std::setw(4) << iteration << ".txt";

        std::ofstream fichier(nomFichier.str());
        
        if (!fichier.is_open()) {
            std::cerr << "[ERREUR] Impossible de créer : " 
                     << nomFichier.str() << std::endl;
            return;
        }

        // Écrire dimensions (hauteur largeur)
        fichier << grille->getHauteur() << " " << grille->getLargeur() << "\n";

        // Écrire la grille (format réutilisable)
        for (int y = 0; y < grille->getHauteur(); ++y) {
            for (int x = 0; x < grille->getLargeur(); ++x) {
                NS_Modele::Cellule* cellule = grille->obtenirCellule(x, y);
                
                // Écrire selon le type de cellule
                if (cellule->estObstacle()) {
                    fichier << "2";  // Obstacle
                } else if (cellule->estVivante()) {
                    fichier << "1";  // Vivante
                } else {
                    fichier << "0";  // Morte
                }
                
                if (x < grille->getLargeur() - 1) {
                    fichier << " ";
                }
            }
            fichier << "\n";
        }

        fichier.close();
    }

    bool GestionFichier::validerFormat(const std::string& cheminFichier) {
        std::ifstream fichier(cheminFichier);
        
        if (!fichier.is_open()) {
            return false;
        }

        try {
            std::string premiereLigne;
            std::getline(fichier, premiereLigne);
            
            std::istringstream iss(premiereLigne);
            int hauteur, largeur;  // ← Corrigé : hauteur d'abord
            
            if (!(iss >> hauteur >> largeur)) {  // ← Corrigé
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

}