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
            int largeur, hauteur;
            char modeTorique = 'F';
            
            iss >> largeur >> hauteur;
            
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
                for (int x = 0; x < largeur && x < static_cast<int>(lignes[y].length()); ++x) {
                    char c = lignes[y][x];
                    NS_Modele::Cellule* cellule = nullptr;

                    switch (c) {
                        case '1':
                        case 'O':
                        case 'o':
                            cellule = new NS_Modele::CelluleVivante();
                            break;
                        case '#':
                        case 'X':
                        case 'x':
                            cellule = new NS_Modele::CelluleObstacle();
                            break;
                        case '0':
                        case '.':
                        case ' ':
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
            std::cout << "[INFO] Grille chargee avec succes: " << largeur << "x" << hauteur 
                      << (torique ? " (mode torique)" : " (mode non-torique)") << std::endl;
            
            return grille;

        } catch (const std::exception& e) {
            std::cerr << "[ERREUR] Erreur lors du chargement: " << e.what() << std::endl;
            fichier.close();
            return nullptr;
        }
    }

    void GestionFichier::sauvegarderGrille(const std::string& cheminFichier, 
                                           NS_Modele::Grille* grille, 
                                           int iteration) {
        if (!grille) {
            std::cerr << "[ERREUR] Grille invalide pour la sauvegarde" << std::endl;
            return;
        }

        std::ofstream fichier(cheminFichier);
        
        if (!fichier.is_open()) {
            std::cerr << "[ERREUR] Impossible de creer le fichier: " << cheminFichier << std::endl;
            return;
        }

        try {
            // Première ligne : dimensions et mode
            fichier << grille->getLargeur() << " " << grille->getHauteur();
            if (grille->getModeTorique()) {
                fichier << " T";
            }
            fichier << std::endl;

            // Commentaire avec le numéro d'itération
            fichier << "# Iteration: " << iteration << std::endl;

            // Contenu de la grille
            for (int y = 0; y < grille->getHauteur(); ++y) {
                for (int x = 0; x < grille->getLargeur(); ++x) {
                    NS_Modele::Cellule* cellule = grille->obtenirCellule(x, y);
                    fichier << cellule->getSymbole();
                }
                fichier << std::endl;
            }

            fichier.close();
            std::cout << "[INFO] Grille sauvegardee dans: " << cheminFichier << std::endl;

        } catch (const std::exception& e) {
            std::cerr << "[ERREUR] Erreur lors de la sauvegarde: " << e.what() << std::endl;
            fichier.close();
        }
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

}