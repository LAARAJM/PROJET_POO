#pragma once

#include "JdV/Vue/Affichage.hpp"
#include <string>

namespace JdV {
namespace Vue {


class AffichageConsole : public Affichage {
private:
 
    std::string cheminBaseFichier; 
public:
    AffichageConsole(const std::string& cheminBase);
    

    void initialiser() override;
    void nettoyer() override;


    void afficher(const JdV::Modele::Grille& grille, int iteration) override;
    

    bool estOuvert() const override { return true; } 
    void gererEntree() override {} 
};

} 
} 