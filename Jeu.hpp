#pragma once

#include <vector>
#include <string>

namespace NS_Modele {
    class Grille;
    class Regle;
}

namespace NS_Vue {
    class Affichage;
}

namespace NS_Controleur {

    class Jeu {
    private:
        NS_Modele::Grille* grille;
        NS_Modele::Regle* regle;
        NS_Vue::Affichage* affichage;
        int iterationCourante;
        int iterationsMax;
        std::vector<NS_Modele::Grille*> grillesPrecedentes;

        void sauvegarderIterationCourante();

    public:
        Jeu(NS_Modele::Grille* g, NS_Modele::Regle* r, NS_Vue::Affichage* a, int nbIterations);
        
        ~Jeu();

        void executer();

        void initialiser();

        void etape();

        bool doitArreter();

        bool estStable();

        int getIteration() const;

    };

}