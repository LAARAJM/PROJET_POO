#pragma once

#include <string>
#include <memory>
// Déclaration anticipée pour la dépendance Grille
namespace JdV { namespace Modele { class Grille; } }

namespace JdV {
namespace Vue {


class Affichage {
public:
    virtual ~Affichage() = default;
    


    virtual void initialiser() = 0;
    virtual void nettoyer() = 0;


    virtual void afficher(const JdV::Modele::Grille& grille, int iteration) = 0;
    

    virtual bool estOuvert() const { return true; } 

    
    virtual void gererEntree() {} 
};

} 
} 