#ifndef FABRIQUEJEU_HPP
#define FABRIQUEJEU_HPP

#include <string>
#include "Grille.hpp"
#include "Regle.hpp"
#include "Affichage.hpp"
#include "Jeu.hpp"

namespace Controleur {

class FabriqueJeu {
public:
    
    static Jeu* creerDepuisFichier(const std::string& fichier, 
                                    const std::string& mode, 
                                    int iterMax = -1);
   
   
};

} 

#endif 