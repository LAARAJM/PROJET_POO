#pragma once
#include "Grille.hpp"

namespace NS_Vue {
    class Affichage {

    public:

        virtual void initialiser()=0;
        virtual void afficher(NS_Modele::Grille* grille, int n)=0;
        virtual void nettoyer()=0;
        virtual void afficherMessage(const char* message)=0;
    
    };

};

