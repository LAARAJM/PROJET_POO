#pragma once

#include "Cellule.hpp" 

namespace NS_Modele { //Namespace du modèle
    class CelluleVivante : public Cellule { //Cellule Vivante hérite de la classe abstraite Cellule
    public:
        CelluleVivante(); //Constructeur de la Cellule vivante
        virtual ~CelluleVivante() = default; //Destructeur virtuel par défaut

        virtual bool estVivante() override; //Indique que la cellule est vivante

        virtual char getSymbole() override; //Retourne le symbole de la cellule

        virtual bool estObstacle() override; //Indique si la cellule est un obstacle

        virtual Cellule* clone() override; //Retourne une copie polymorphique de la cellule 

    };
}