#pragma once

#include "Cellule.hpp" 

namespace NS_Modele {
    class CelluleVivante : public Cellule {
    public:
        CelluleVivante();
        virtual ~CelluleVivante() = default;

        virtual bool estVivante() override;

        virtual char getSymbole() override;

        virtual bool estObstacle() override;

        virtual Cellule* clone() override; 

    };
}