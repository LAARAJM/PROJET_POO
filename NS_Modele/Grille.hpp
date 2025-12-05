#pragma once

#include <vector>
#include "Cellule.hpp"
#include "Regle.hpp"

namespace NS_Modele { //Namespace du modèle

    class Grille { //Déclaration de la classe Grille
    private:
        std::vector<std::vector<Cellule*>> cellules; //Tableau 2D de pointeurs vers des cellules
        int largeur; //Largeur de la grille
        int hauteur; //Hauteur de la grille
        bool modeTorique; //Indique si la grille utilise le mode torique
 
        void detruireCellules(); //Supprime toutes les cellules

    public:

        ~Grille(); //Destructeur de la grille

        Grille(int largeur, int hauteur, bool torique = false); //Constructeur de la grille

        Grille(const Grille& autre) = delete; //Copie interdite

        Grille& operator = (const Grille& autre) = delete; //Affectation interdite

        void mettreAJour(Regle* regle); //Met à jour la grille selon une règle d'évolution

        Cellule* obtenirCellule(int x, int y) const; //Retourne une cellule à une position donnée

        void definirCellule(int x, int y, Cellule* nouvelleCellule); //Définit une cellule à une position

        int compterVoisinsVivants(int x, int y) const; //Compte les voisins autour d'une cellule

        Grille* clone() const; //Retourne une copie complète de la grille
        
        bool estIdentique(const Grille* autre) const; //Compare deux grilles cellules par cellule

        int getLargeur() const { //Accesseur largeur
            return largeur; 
        }

        int getHauteur() const { //Accesseur hauteur
            return hauteur; 
        }
        
        bool getModeTorique() const { //Accesseur du mode torique
            return modeTorique; 
        }
        
        void setModeTorique(bool torique) { //Mutateur du mode torique
            modeTorique = torique; 
        }
    };
}