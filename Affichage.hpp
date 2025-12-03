#pragma once

#include <string>

// Forward declaration
namespace NS_Modele {
    class Grille;
}

namespace NS_Vue {


    class Affichage {
    public:
        virtual ~Affichage() = default;

        virtual void initialiser() = 0;

        virtual void afficher(NS_Modele::Grille* grille, int n) = 0;

        virtual void nettoyer() = 0;

        virtual void afficherMessage(const std::string& message) = 0;
    };

}
