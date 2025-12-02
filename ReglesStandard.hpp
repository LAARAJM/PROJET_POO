#pragma once

#include "Regle.hpp"
#include "CelluleVivante.hpp"
#include "CelluleMorte.hpp"


namespace NS_Modele {

    class ReglesStandard : public Regle {
    public:

        ReglesStandard() = default;

        virtual ~ReglesStandard() = default;

        virtual Cellule* obtenirNouvelEtat(Cellule* celluleActuelle, int nbVoisinsVivants) override;
        
    };
}