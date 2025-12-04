#pragma once

#include <string>
#include "Affichage.hpp"

namespace NS_Modele {
    class Grille;
}

namespace NS_Vue {

    class AffichageConsole : public Affichage {
    private:
        int numeroIteration;

    public:

        AffichageConsole();


        void initialiser() override;

        void afficher(NS_Modele::Grille* grille, int n) override;

 
        void nettoyer() override;

  
        void afficherMessage(const std::string& message) override;
    };

}
