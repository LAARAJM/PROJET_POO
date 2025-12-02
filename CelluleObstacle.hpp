#pragma once

#include "Cellule.hpp" 

namespace NS_Modele {

    class CelluleObstacle : public Cellule {
    public:

        CelluleObstacle();

        virtual ~CelluleObstacle() = default;

        virtual bool estVivante() override;

        virtual char getSymbole() override;

        virtual bool estObstacle() override;

        virtual Cellule* clone() override; 

    };
}