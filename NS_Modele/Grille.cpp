#include "Grille.hpp"
#include "CelluleMorte.hpp"

namespace NS_Modele { //Namespace du modèle

    Grille::Grille(int largeur, int hauteur, bool torique) //Contructeur de la grille
        : largeur(largeur), hauteur(hauteur), modeTorique(torique) { //Initialisation des attributs
    
        cellules.resize(hauteur); //Redimensionne le tableau de lignes
        for (int y = 0; y < hauteur; y++) { //Parcourt chaque ligne
            cellules[y].resize(largeur); //Redimensionne chaque ligne
            for (int x = 0; x < largeur; x++) { //Parcourt chaque colonne
                cellules[y][x] = new CelluleMorte(); //Initialise chaque cellule comme morte
            }
        }
    }

    Grille::~Grille() { //Destructeur de la grille
        detruireCellules(); //Libère toute la mémoire des cellules 
    }

    void Grille::detruireCellules() { //Méthode pour supprimer toutes les cellules
        for (int y = 0; y < hauteur; y++) { //Parcourt toutes les lignes 
            for (int x = 0; x < largeur; x++) { //Parcourt toutes les colonnes
                delete cellules[y][x]; //Supprimé la cellule
                cellules[y][x] = nullptr; //Met le pointeur à nullptr
            }
        }
    }

    void Grille::mettreAJour(Regle* regle) { //Met à jourt la grille selon une règle
        std::vector<std::vector<Cellule*>> nouvelleGrille(hauteur); //Nouvelle grille temporaire
        
        for (int y = 0; y < hauteur; y++) { //Parcourt chaque ligne
            nouvelleGrille[y].resize(largeur); //Redimensionne la ligne 
            for (int x = 0; x < largeur; x++) { //Parcourt chaque cellule
                int voisinsVivants = compterVoisinsVivants(x, y); //Compte les voisins vivants
                nouvelleGrille[y][x] = regle->obtenirNouvelEtat(cellules[y][x], voisinsVivants); //Applique la règle et crée la nouvelle cellule
            }
        }
        detruireCellules(); //Supprime l'ancienne grille
        cellules = nouvelleGrille; //Remplace par la nouvelle grille
    }


    Cellule* Grille::obtenirCellule(int x, int y) const { //Retourne une cellule si valide
        if (x >= 0 && x < largeur && y >= 0 && y < hauteur) { //Vérifie que les coordonnées sont valides
            return cellules[y][x]; //Retourne la cellule
        }
        return nullptr; //Sinon retourne nullptr 
    }

    void Grille::definirCellule(int x, int y, Cellule* nouvelleCellule) { //Définit une cellule
        if (x >= 0 && x < largeur && y >= 0 && y < hauteur) { //Vérifie coordonnées
            delete cellules[y][x]; //Supprime l'ancienne cellule
            cellules[y][x] = nouvelleCellule; //Place la nouvelle cellule 
        }
    }

    int Grille::compterVoisinsVivants(int x, int y) const { //Compte les voisins vivants d'une cellule
        int compteur = 0; //Initialise le compteur
        for (int dy = -1; dy <= 1; dy++) { //Parcourt les lignes voisines 
            for (int dx = -1; dx <= 1; dx++) { //Parcourt les colonnes voisines

                if (dx == 0 && dy == 0) continue; // Parcourt les colonnes voisines
                
                int voisinX = x + dx; //Calcul de x du voisin
                int voisinY = y + dy; //Calcul de y du voisin
                
                if (modeTorique) { //Si la grille est torique
                    voisinX = (voisinX + largeur) % largeur; //Applique l'effet torique horizontale
                    voisinY = (voisinY + hauteur) % hauteur; //Applique l'effet torique verticale
                }
                
                if (voisinX >= 0 && voisinX < largeur && //Vérifie coordonnées valides
                    voisinY >= 0 && voisinY < hauteur) {
                    
                    if (cellules[voisinY][voisinX]->estVivante()) { //Si le voisin est vivant
                        compteur++; //Incrémente le compteur
                    }
                }
            }
        }
        
        return compteur; //Retourne le nombre de voisins vivants
    }


    Grille* Grille::clone() const { //Clone la grille entière
        Grille* nouvelleGrille = new Grille(largeur, hauteur, modeTorique); //Crée une nouvelle grille
        
        for (int y = 0; y < hauteur; y++) { //Parcourt chaque ligne 
            for (int x = 0; x < largeur; x++) { //Parcourt chaque cellule
                delete nouvelleGrille->cellules[y][x]; //Supprime la cellule morte par défaut
                nouvelleGrille->cellules[y][x] = cellules[y][x]->clone(); //Clone la cellule réelle
            }
        }
        return nouvelleGrille; //Retourne la grille clonée
    }

    bool Grille::estIdentique(const Grille* autre) const { //Compare deux grilles
        if (!autre) return false; //Vérifie que l'autre grille existe
        if (largeur != autre->largeur || hauteur != autre->hauteur) return false; //Vérifie les dimensions identiques
        
        for (int y = 0; y < hauteur; y++) { //Parcourt les lignes
            for (int x = 0; x < largeur; x++) { //Parcourt les colonnes
                if (cellules[y][x]->estVivante() != autre->cellules[y][x]->estVivante()) { //Compare l'état de chaque cellule
                    return false; //Différence trouvée 
                }
            }
        }
        return true; //Les grilles sont identiques
    }

}
