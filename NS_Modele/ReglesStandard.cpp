#include "ReglesStandard.hpp"
#include "CelluleObstacle.hpp"

namespace NS_Modele { //Namespace du modèle

    Cellule* ReglesStandard::obtenirNouvelEtat(Cellule* celluleActuelle, int nbVoisinsVivants) { //Calcul le nouvel état selon les règles du Jeu de la VIe

        if (celluleActuelle->estObstacle()) { //Si la cellule est un obstacle
            return celluleActuelle->clone(); //Elle reste identique
        }

        if (celluleActuelle->estVivante()) { //Si la cellule est vivante
            if (nbVoisinsVivants == 2 || nbVoisinsVivants == 3) { //Elle survit avec 2 ou 3 voisins
                return celluleActuelle->clone(); //La cellule reste vivante
            } else {
                return new CelluleMorte(); //Sinon elle meurt
            }
        }
        
        else { //Si la cellule est morte
            if (nbVoisinsVivants == 3) { //Elle naît si elle a exactement 3 voisin vivants

                return new CelluleVivante(); //Nouvelle cellule vivante
            } else {
                return celluleActuelle->clone(); //Sinon elle reste morte
            }
        }
        
    }
}