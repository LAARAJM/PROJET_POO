#include "CelluleVivante.hpp"
#include <iostream>

namespace NS_Modele {

    CelluleVivante::CelluleVivante() {}

    bool CelluleVivante::estVivante() {
        return true;
    }

    char CelluleVivante::getSymbole() {
        return 'O'; 
    }

    bool CelluleVivante::estObstacle() {
        return false;
    }

    Cellule* CelluleVivante::clone() {
        return new CelluleVivante(*this);
    }
    
}