#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>


namespace JdV { namespace Modele { class Grille; } } 

namespace JdV {
namespace Utils {

struct DonneesGrille {
    int hauteur = 0;
    int largeur = 0;
    std::vector<std::vector<int>> cellules;
};

class GestionFichier {
public:
    // Lire le fichier
    static DonneesGrille lireFichier(const std::string& cheminFichier);

    // L'écriture du fichier de sortie
    static void ecrireFichier(const std::string& cheminFichier, const JdV::Modele::Grille& grille, int iteration);
};

} 
} 