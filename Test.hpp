#pragma once

#include <string>
#include <vector>

namespace NS_Modele {
    class Grille;
}

namespace NS_Test {

    class TestRunner {
    private:
        int testsReussis;
        int testsEchoues;

    public:
        TestRunner();
        void afficherResultat(const std::string& nomTest, bool succes, const std::string& detail = "");
        void afficherBilan();
        bool tousReussis() const;
    };

    class Test {
    private:
        static NS_Modele::Grille* creerGrille(int largeur, int hauteur, const std::vector<std::vector<int>>& etat);
        static void sauvegarderGrilleDansFichier(const std::string& nomFichier, const std::vector<std::vector<int>>& etat, bool torique = false);
        static bool comparerGrilles(NS_Modele::Grille* grille1, NS_Modele::Grille* grille2);
        static void afficherGrille(NS_Modele::Grille* grille, const std::string& titre = "");

        static bool test1_BlocStable(TestRunner& runner);
        static bool test2_Extinction(TestRunner& runner);
        static bool test3_Planeur(TestRunner& runner);
        static bool test4_Clignotant(TestRunner& runner);
        static bool test5_Obstacles(TestRunner& runner);
        static bool test6_ModeTorique(TestRunner& runner);
        static bool test7_GrilleVide(TestRunner& runner);
        static bool test8_ReglesConway(TestRunner& runner);
        static bool test9_ChargementFichier(TestRunner& runner);
        static bool test10_DetectionStabilisation(TestRunner& runner);

    public:
        static bool executerTousLesTests();
    };

}