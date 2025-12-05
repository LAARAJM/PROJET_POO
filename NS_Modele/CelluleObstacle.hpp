#pragma once

#include "Cellule.hpp" 

namespace NS_Modele { //Namespace du modèle

    class CelluleObstacle : public Cellule { //Cellule obstacle hérite de la classe abstraite Cellule
    public:

        CelluleObstacle(); //Constructeur de la cellule obstacle

        virtual ~CelluleObstacle() = default; //Destructeur virtuel par défaut

        virtual bool estVivante() override; //Indique si la cellule est vivante

        virtual char getSymbole() override; //Retourne le symbole représentant la cellule

        virtual bool estObstacle() override; //Indique si la cellule est un obstacle 

        virtual Cellule* clone() override; //Crée une copie polymorphique de la cellule 

    };
}