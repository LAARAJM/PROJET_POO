#include "CelluleObstacle.hpp"

namespace NS_Modele { //Namespace du modèle

    CelluleObstacle::CelluleObstacle() {} //Constructeur de la cellule obstacle


    bool CelluleObstacle::estVivante() { //Indique si la cellule est vivante
        return false; //Une cellule obstacle n'est jamais vivante
    }

    char CelluleObstacle::getSymbole() { //Retourne le symbole représentant la cellule
        return '#'; //'#' représente une cellule obstacle
    }

    bool CelluleObstacle::estObstacle() { //Indique si la cellule est un obstacle
        return true; //Cette cellule est un obstacle
    }

    Cellule* CelluleObstacle::clone() { //Crée une copie polymorphique de la cellule
        return new CelluleObstacle(*this); //Retourne une nouvelle instance copiée
    }
    
}