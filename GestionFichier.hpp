#pragma once

#include <string>

namespace NS_Modele {
    class Grille;
}

namespace NS_Controleur {

    class GestionFichier {
    public:
        static NS_Modele::Grille* chargerGrille(const std::string& cheminFichier);
        
        static void sauvegarderGrille(const std::string& cheminFichier, 
                                      NS_Modele::Grille* grille, 
                                      int iteration);
        
        static bool validerFormat(const std::string& cheminFichier);
    };

}