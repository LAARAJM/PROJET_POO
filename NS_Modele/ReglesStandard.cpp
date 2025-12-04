#include "ReglesStandard.hpp"
#include "CelluleObstacle.hpp"

namespace NS_Modele {

    Cellule* ReglesStandard::obtenirNouvelEtat(Cellule* celluleActuelle, int nbVoisinsVivants) {

        if (celluleActuelle->estObstacle()) {
            return celluleActuelle->clone();
        }

        if (celluleActuelle->estVivante()) {
            if (nbVoisinsVivants == 2 || nbVoisinsVivants == 3) {
                return celluleActuelle->clone(); 
            } else {
                return new CelluleMorte();
            }
        }
        
        else { 
            if (nbVoisinsVivants == 3) {

                return new CelluleVivante();
            } else {
                return celluleActuelle->clone();
            }
        }
        
    }
}