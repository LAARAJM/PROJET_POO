#include "CelluleObstacle.hpp"

namespace NS_Modele {

    CelluleObstacle::CelluleObstacle() {}


    bool CelluleObstacle::estVivante() {
        return false; 
    }

    char CelluleObstacle::getSymbole() {
        return '#'; 
    }

    bool CelluleObstacle::estObstacle() {
        return true; 
    }

    Cellule* CelluleObstacle::clone() {
        return new CelluleObstacle(*this);
    }
    
}