#include "CelluleMorte.hpp"

namespace NS_Modele { //Namespace du modèle


    CelluleMorte::CelluleMorte() {} //Constructeur d'une cellule morte


    bool CelluleMorte::estVivante() { //Méthode indiquant si la cellule est vivante
        return false; //Une cellule morte n'est jamais vivante
    }


    char CelluleMorte::getSymbole() { //Retourne le symbole associé à la cellule
        return '0'; //'0' représente une cellule morte
    }


    bool CelluleMorte::estObstacle() { //Indique si la cellule est un obstacle
        return false; //Une cellule morte n'est pas un obstacle
    }


    Cellule* CelluleMorte::clone() { //Crée une copie polymorphique de la cellule 
        return new CelluleMorte(*this); //Retourne une nouvelle instance copiée
    }
    
}