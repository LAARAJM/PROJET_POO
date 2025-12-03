#ifndef GESTIONFICHIER_HPP
#define GESTIONFICHIER_HPP

#include <string>
#include "Grille.hpp"

namespace Controleur {

class GestionFichier {
public:
    

    static NS_Modele::Grille* chargerGrille(const std::string& cheminFichier);


    static void sauvegarderGrille(const std::string& cheminFichier, 
                                   const NS_Modele::Grille* grille, 
                                   int iteration);

 
    static bool validerFormat(const std::string& cheminFichier);

private:
    
    static bool fichierExiste(const std::string& chemin);
    static void afficherErreur(const std::string& message);
};

} 
#endif 