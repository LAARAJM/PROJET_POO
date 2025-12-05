#include "Position.hpp"

namespace NS_Modele { //Namespace du modèle

    bool Position::estValide(int largeurMax, int hauteurMax) { //Vérifie si la position est dans les limites
        return x >= 0 && x < largeurMax && y >= 0 && y < hauteurMax; //Retourne true si x et y sont dans la grille, sinon false
    }
}