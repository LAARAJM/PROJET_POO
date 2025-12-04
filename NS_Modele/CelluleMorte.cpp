#include "CelluleMorte.hpp"

namespace NS_Modele {


    CelluleMorte::CelluleMorte() {}


    bool CelluleMorte::estVivante() {
        return false;
    }


    char CelluleMorte::getSymbole() {
        return '0'; 
    }


    bool CelluleMorte::estObstacle() {
        return false;
    }


    Cellule* CelluleMorte::clone() {
        return new CelluleMorte(*this);
    }
    
}