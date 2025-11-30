#pragma once

#include <memory>
#include <string>

namespace JdV { namespace Modele { class Grille; } }
namespace JdV { namespace Regles { class Regle; } }
namespace JdV { namespace Vue { class Affichage; } }
namespace JdV { namespace Controlleur { class Iterations; } }

namespace JdV {
namespace Controlleur {


class Jeu {
private:

    std::unique_ptr<Modele::Grille> grille;
    std::unique_ptr<Regles::Regle> regle;
    std::unique_ptr<Vue::Affichage> affichage;
    std::unique_ptr<Iterations> gestionnaireIterations;
    
    std::string nomFichierEntree;

public:
    Jeu() = default;

    void initialiser(const std::string& cheminFichier, const std::string& mode, bool torique = false);

    void executer();


    bool etape();
};

} 
}