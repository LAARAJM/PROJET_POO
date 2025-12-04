#pragma once

#include "Cellule.hpp" 

namespace NS_Modele {

    class CelluleMorte : public Cellule {
    public:

        CelluleMorte();

        virtual ~CelluleMorte() = default;

        virtual bool estVivante() override;

        virtual char getSymbole() override;

        virtual bool estObstacle() override;

        virtual Cellule* clone() override; 
        
    };
}