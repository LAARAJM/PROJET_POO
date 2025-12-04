#pragma once

#include <string>
#include <vector>

namespace NS_Modele {
    class Grille;
}

namespace NS_Test {

    // Collecte et affiche les résultats des tests
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

    // Classe contenant les tests unitaires du Jeu de la Vie
    class Test {
    private:
        // Utilitaires pour les tests
        static NS_Modele::Grille* creerGrille(int largeur, int hauteur, const std::vector<std::vector<int>>& etat);
        static void sauvegarderGrilleDansFichier(const std::string& nomFichier, const std::vector<std::vector<int>>& etat, bool torique = false);
        static bool comparerGrilles(NS_Modele::Grille* grille1, NS_Modele::Grille* grille2);
        static void afficherGrille(NS_Modele::Grille* grille, const std::string& titre = "");

        // Tests unitaires
        static bool test1_BlocStable(TestRunner& runner);           // Motif stable (bloc 2x2)
        static bool test2_Extinction(TestRunner& runner);           // Cellules isolées meurent
        static bool test3_Planeur(TestRunner& runner);              // Motif mobile sur 4 itérations
        static bool test4_Clignotant(TestRunner& runner);           // Oscillateur période 2
        static bool test5_Obstacles(TestRunner& runner);            // Obstacles restent immuables
        static bool test6_ModeTorique(TestRunner& runner);          // Bords connectés vs normaux
        static bool test7_GrilleVide(TestRunner& runner);           // Grille vide reste vide
        static bool test8_ReglesConway(TestRunner& runner);         // Règles de base (2-3, 3)
        static bool test9_ChargementFichier(TestRunner& runner);    // Lecture fichier et simulation
        static bool test10_DetectionStabilisation(TestRunner& runner); // Détection motif stable

    public:
        static bool executerTousLesTests();
    };

}