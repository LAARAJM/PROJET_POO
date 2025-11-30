#pragma once

#include "Cellule.hpp"
#include "GestionFichier.hpp"
#include <vector>
#include <memory>
#include <stdexcept>

namespace JdV { namespace Regles { class Regle; } }

namespace JdV {
namespace Modele {


class Grille {
private:
    int largeur;
    int hauteur;
    bool estTorique;
    std::vector<std::vector<std::unique_ptr<Cellule>>> cellules;

    int compterVoisinsVivants(int x, int y) const;

public:

    Grille(int h, int l, bool torique);

    Grille(const Grille&) = delete;
    Grille& operator=(const Grille&) = delete;

    static std::unique_ptr<Grille> creerDepuisDonnees(JdV::Utils::DonneesGrille donnees, bool torique);


    std::unique_ptr<Grille> evoluer(const JdV::Regles::Regle& regle) const;

    // Accesseurs
    int getLargeur() const { return largeur; }
    int getHauteur() const { return hauteur; }
    const Cellule& getCellule(int y, int x) const;
    

    bool operator==(const Grille& autre) const;
};

} 
} 