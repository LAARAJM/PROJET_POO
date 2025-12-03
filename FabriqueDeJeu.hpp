#pragma once

#include <string>
#include "Jeu.hpp"
#include "GestionFichier.hpp"

namespace NS_Controleur {

    class FabriqueDeJeu {
    public:
        static NS_Controleur::Jeu* creerDepuisFichier(const std::string& fichier, 
                                        const std::string& mode, 
                                        int iterMax = -1);
    };

} 

 