#include "CelluleVivante.hpp"
#include <iostream>

namespace NS_Modele { //Namespace du modèle

    CelluleVivante::CelluleVivante() {} //Constructeur de la cellule vivante

    bool CelluleVivante::estVivante() { //Indique si la cellule est vivante
        return true; //Une cellule vivante est toujours vivante
    }

    char CelluleVivante::getSymbole() { //Retourne le symbole représentant la cellule
        return '1'; //'1' représente une cellule vivante dans la grille
    }

    bool CelluleVivante::estObstacle() { //Indique si la cellule est un obstacle
        return false; //Une cellule vivante n'est pas un obstacle
    }

    Cellule* CelluleVivante::clone() { //Crée une copie polymorphique de la cellule
        return new CelluleVivante(*this); //Retourne une nouvelle instance copiée
    }
    
}