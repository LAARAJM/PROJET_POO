#pragma once

#include "Cellule.hpp" 

namespace NS_Modele { //Namespace du modèle

    class CelluleMorte : public Cellule { //Cellule Morte hérite de la classe abstraite Cellule
    public:

        CelluleMorte(); //Constructeur de la cellule morte

        virtual ~CelluleMorte() = default; //Destructeur virtuel par défaut

        virtual bool estVivante() override; //Indique si la cellule est vivante

        virtual char getSymbole() override; //Retourne le symbole représentant la cellule

        virtual bool estObstacle() override; //Indique si c'est un obstacle 

        virtual Cellule* clone() override; //Retourne une copie polymorphique de l'objet
        
    };
}