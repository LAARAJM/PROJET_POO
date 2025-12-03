#pragma once

#include <vector>
#include "Cellule.hpp"
#include "Regle.hpp"

namespace NS_Modele {

    class Grille {
    private:
        std::vector<std::vector<Cellule*>> cellules;
        int largeur;
        int hauteur;
        bool modeTorique;
 
        void detruireCellules(); 

    public:

        Grille(int largeur, int hauteur, bool torique = false); 

        Grille(const Grille& autre) = delete;

        Grille& operator=(const Grille& autre) = delete;

        void mettreAJour(Regle* regle);

        Cellule* obtenirCellule(int x, int y) const;

        void definirCellule(int x, int y, Cellule* nouvelleCellule);

        int compterVoisinsVivants(int x, int y) const;

        Grille* clone() const;
        
        bool estIdentique(const Grille* autre) const;

        int getLargeur() const { 
            return largeur; 
        }

        int getHauteur() const { 
            return hauteur; 
        }
        
        bool getModeTorique() const { 
            return modeTorique; 
        }
        
        void setModeTorique(bool torique) { 
            modeTorique = torique; 
        }
    };
}