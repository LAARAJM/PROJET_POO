#include "Grille.hpp"
#include "CelluleMorte.hpp"

namespace NS_Modele {

    Grille::Grille(int largeur, int hauteur, bool torique)
        : largeur(largeur), hauteur(hauteur), modeTorique(torique) {
    
        cellules.resize(hauteur);
        for (int y = 0; y < hauteur; y++) {
            cellules[y].resize(largeur);
            for (int x = 0; x < largeur; x++) {
                cellules[y][x] = new CelluleMorte();
            }
        }
    }

    Grille::~Grille() {
        detruireCellules();
    }

    void Grille::detruireCellules() {
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                delete cellules[y][x];
                cellules[y][x] = nullptr;
            }
        }
    }

    void Grille::mettreAJour(Regle* regle) {
        std::vector<std::vector<Cellule*>> nouvelleGrille(hauteur);
        
        for (int y = 0; y < hauteur; y++) {
            nouvelleGrille[y].resize(largeur);
            for (int x = 0; x < largeur; x++) {
                int voisinsVivants = compterVoisinsVivants(x, y);
                nouvelleGrille[y][x] = regle->obtenirNouvelEtat(cellules[y][x], voisinsVivants);
            }
        }
        detruireCellules();
        cellules = nouvelleGrille;
    }


    Cellule* Grille::obtenirCellule(int x, int y) const {
        if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
            return cellules[y][x];
        }
        return nullptr;
    }

    void Grille::definirCellule(int x, int y, Cellule* nouvelleCellule) {
        if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
            delete cellules[y][x];
            cellules[y][x] = nouvelleCellule;
        }
    }

    int Grille::compterVoisinsVivants(int x, int y) const {
        int compteur = 0;
        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {

                if (dx == 0 && dy == 0) continue;
                
                int voisinX = x + dx;
                int voisinY = y + dy;
                
                if (modeTorique) {
                    voisinX = (voisinX + largeur) % largeur;
                    voisinY = (voisinY + hauteur) % hauteur;
                }
                
                if (voisinX >= 0 && voisinX < largeur && 
                    voisinY >= 0 && voisinY < hauteur) {
                    
                    if (cellules[voisinY][voisinX]->estVivante()) {
                        compteur++;
                    }
                }
            }
        }
        
        return compteur;
    }


    Grille* Grille::clone() const {
        Grille* nouvelleGrille = new Grille(largeur, hauteur, modeTorique);
        
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                delete nouvelleGrille->cellules[y][x];
                nouvelleGrille->cellules[y][x] = cellules[y][x]->clone();
            }
        }
        return nouvelleGrille;
    }

    bool Grille::estIdentique(const Grille* autre) const {
        if (!autre) return false;
        if (largeur != autre->largeur || hauteur != autre->hauteur) return false;
        
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                if (cellules[y][x]->estVivante() != autre->cellules[y][x]->estVivante()) {
                    return false;
                }
            }
        }
        return true;
    }

}
