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

namespace NS_Controleur { //Début du namespace Controleur

    NS_Modele::Grille* GestionFichier::chargerGrille(const std::string& cheminFichier) { //Début de la fonction de changement
        std::ifstream fichier(cheminFichier); //Ouvre le fichier en lecture
        
        if (!fichier.is_open()) { //Vérifier si l'ouverture a échoué
            std::cerr << "[ERREUR] Impossible d'ouvrir le fichier: " << cheminFichier << std::endl; //Message d'erreur
            return nullptr; //Retourne nullptr
        }

        try { //Bloc try pour gérer les exceptions
            std::string premiereLigne; //Stocke la première ligne du fichier
            std::getline(fichier, premiereLigne); //Lit la première ligne
            
            std::istringstream iss(premiereLigne); // Crée un flux de lecture
            int hauteur, largeur; //Variables hauteur et largeur de la grille
            char modeTorique = 'F'; //Mode torique non mis par défaut
            
            iss >> hauteur >> largeur; //Lit hauteur et largeur
            
            if (iss >> modeTorique) { //Si un caractère supplémentaire existe 
                modeTorique = std::toupper(modeTorique); //Convertit en majus
            }
            
            if (largeur <= 0 || hauteur <= 0) { //Vérifie la validité des dimensions
                std::cerr << "[ERREUR] Dimensions invalides dans le fichier" << std::endl; //Erreur si invalidités
                return nullptr; //Retourn nullptr
            }

            bool torique = (modeTorique == 'T'); //Active le mode torique si "T"
            NS_Modele::Grille* grille = new NS_Modele::Grille(largeur, hauteur, torique); //Crée la grille

            std::vector<std::string> lignes; //Stocke les lignes des cellules
            std::string ligne; //Une ligne temporaire
            
            while (std::getline(fichier, ligne) && lignes.size() < static_cast<size_t>(hauteur)) { //Lit jusqu'à hauteur
                if (!ligne.empty() && ligne[0] != '#') { //Ignore les lignes vides et commentaires
                    lignes.push_back(ligne); //Ajoute la ligne
                }
            }

            if (lignes.size() != static_cast<size_t>(hauteur)) { //Vérifie que le nombre de lignes est correct
                std::cerr << "[ERREUR] Nombre de lignes incorrect dans le fichier" << std::endl; //Erreur
                delete grille; //Nettoie la grille
                return nullptr; //Retourne nullptr
            }

            for (int y = 0; y < hauteur; ++y) { //Parcourt chaque ligne de la grille
                std::istringstream lineStream(lignes[y]); //Flux pour lire les valeurs
                int valeur; //Valeur de la cellule
                int x = 0; //Position en x
                
                while (lineStream >> valeur && x < largeur) { //Lit les valeurs jusqu'à la largeur
                    NS_Modele::Cellule* cellule = nullptr; //Pointeur pour la cellule créé

                    switch (valeur) { //Séléctionne le type de cellule
                        case 1:
                            cellule = new NS_Modele::CelluleVivante(); //Cellule vivante
                            break;
                        case 2:
                            cellule = new NS_Modele::CelluleObstacle(); //Cellule obstacle
                            break;
                        case 0:
                        default:
                            cellule = new NS_Modele::CelluleMorte(); //Cellule morte
                            break;
                    }

                    grille->definirCellule(x, y, cellule); //Place la cellule dans la grille
                    x++; //Passe à la colonne suivante
                }
                
                for (; x < largeur; ++x) { //Complète si la ligne est trop courte
                    grille->definirCellule(x, y, new NS_Modele::CelluleMorte()); //Cellules mortes par défaut
                }
            }

            fichier.close(); //Ferme le fichier
            std::cout << "[INFO] Grille chargee avec succes: " << hauteur << "x" << largeur  //MEssage d'erreur
                      << (torique ? " (mode torique)" : " (mode non-torique)") << std::endl;
            
            return grille; //Retourne la grille chargée

        } catch (const std::exception& e) { //Gestion des erreurs
            std::cerr << "[ERREUR] Erreur lors du chargement: " << e.what() << std::endl; //Affiche le message
            fichier.close(); //Ferme le fichier
            return nullptr; //Retourne nullptr
        }
    }

    void GestionFichier::sauvegarderGrille(const std::string& dossierSortie, //Début de la sauvegarde
                                           NS_Modele::Grille* grille,
                                           int iteration) {
        if (!grille) { //Vérifie que la grille n'est pas nulle
            std::cerr << "[ERREUR] Grille nulle" << std::endl; //Erreur
            return; //Arrête la fonction
        }

        // Création du dossier s'il n'existe pas
        try { //BLoc try pour créer le dossier
            std::filesystem::create_directories(dossierSortie); //Crée le dossier si nécessaire
        } catch (const std::exception& e) { //Capture erreur de création
            std::cerr << "[ERREUR] Impossible de créer le dossier : "
                     << e.what() << std::endl; //Affiche l'erreur
            return; //Arrête la fonction
        }

        std::ostringstream nomFichier; //Crée un flux pour un nom de fichier
        nomFichier << dossierSortie << "/iteration_"  //Ajoute le dossier et "itération_"
                  << std::setfill('0') << std::setw(4) << iteration << ".txt"; //Ajoute l'index formaté

        std::ofstream fichier(nomFichier.str()); //Ouvre le fichier en écriture
        
        if (!fichier.is_open()) { //Vérifie l'ouverture
            std::cerr << "[ERREUR] Impossible de créer : " 
                     << nomFichier.str() << std::endl; //Erreur
            return; //Arrête la fonction
        }


        fichier << grille->getHauteur() << " " << grille->getLargeur() << "\n"; //Écrit dimensions


        for (int y = 0; y < grille->getHauteur(); ++y) { //Parcourt chaque ligne de la grille
            for (int x = 0; x < grille->getLargeur(); ++x) { //PArcourt chaque colonne
                NS_Modele::Cellule* cellule = grille->obtenirCellule(x, y); //Récuère la cellule

                if (cellule->estObstacle()) { //Si obstacle 
                    fichier << "2";  // Écrire 2
                } else if (cellule->estVivante()) { //Si vivante 
                    fichier << "1";  // Écrire 1
                } else { //Si morte 
                    fichier << "0";  // Écrire 2
                }
                
                if (x < grille->getLargeur() - 1) { //Ajoute un espace sauf en fin de ligne
                    fichier << " ";
                }
            }
            fichier << "\n"; //Retour à la ligne 
        }

        fichier.close(); //Ferme le fichier après écriture
    }

    bool GestionFichier::validerFormat(const std::string& cheminFichier) { //Début de la validation
        std::ifstream fichier(cheminFichier); //Ouvre le fichier
        
        if (!fichier.is_open()) { //Vérifie l'ouverture
            return false; //Format invalide
        }

        try { //Bloc try
            std::string premiereLigne; //Stocke la première ligne
            std::getline(fichier, premiereLigne); //Lit la première ligne
            
            std::istringstream iss(premiereLigne); //FLux pour lire la ligne
            int hauteur, largeur;  //Dimensions
            
            if (!(iss >> hauteur >> largeur)) {  //Vérifie que les deux valeurs sont lisibles
                fichier.close(); //Ferme le fichier
                return false; //Format invalide
            }

            if (largeur <= 0 || hauteur <= 0 || largeur > 1000 || hauteur > 1000) { //Limites de sécurités
                fichier.close(); //Ferme
                return false; //Format invalide
            }

            int compteurLignes = 0; //Compte les lignes volidés
            std::string ligne; //Ligne temp
            
            while (std::getline(fichier, ligne) && compteurLignes < hauteur) { //Parcourt le fichier
                if (!ligne.empty() && ligne[0] != '#') { //Ignore les commentaires
                    compteurLignes++; //Compte les lignes de la grilles 
                }
            }

            fichier.close(); //Ferme le fichier
            return compteurLignes == hauteur; //True si bon nombre de lignes 

        } catch (const std::exception&) { //En cas d'erreur
            fichier.close(); //Ferme
            return false; //Format invalide
        }
    }

}