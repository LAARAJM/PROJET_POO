#include "Test.hpp"
#include "Grille.hpp"
#include "Cellule.hpp"
#include "CelluleVivante.hpp"
#include "CelluleMorte.hpp"
#include "CelluleObstacle.hpp"
#include "ReglesStandard.hpp"
#include "FabriqueDeJeu.hpp"
#include "Jeu.hpp"
#include "GestionFichier.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

namespace NS_Test {
   
    TestRunner::TestRunner() : testsReussis(0), testsEchoues(0) {}
    
    void TestRunner::afficherResultat(const std::string& nomTest, bool succes, const std::string& detail) {
        if (succes) {
            std::cout << "[OK] " << nomTest << std::endl;
            testsReussis++;
        } else {
            std::cout << "[ECHEC] " << nomTest;
            if (!detail.empty()) {
                std::cout << " - " << detail;
            }
            std::cout << std::endl;
            testsEchoues++;
        }
    }
    
    void TestRunner::afficherBilan() {
        std::cout << "\n========================================" << std::endl;
        std::cout << "Tests reussis: " << testsReussis << std::endl;
        std::cout << "Tests echoues: " << testsEchoues << std::endl;
        std::cout << "Total: " << (testsReussis + testsEchoues) << std::endl;
        std::cout << "========================================\n" << std::endl;
    }
    
    bool TestRunner::tousReussis() const {
        return testsEchoues == 0;
    }

    // Crée une grille à partir d'une matrice d'états (0=morte, 1=vivante, 2=obstacle)
    NS_Modele::Grille* Test::creerGrille(int largeur, int hauteur, const std::vector<std::vector<int>>& etat) {
        NS_Modele::Grille* grille = new NS_Modele::Grille(largeur, hauteur, false);
        
        // Parcours de la matrice pour créer les cellules
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                NS_Modele::Cellule* cellule = nullptr;
                
                int valeur = etat[y][x];
                if (valeur == 1) {
                    cellule = new NS_Modele::CelluleVivante();
                } else if (valeur == 2) {
                    cellule = new NS_Modele::CelluleObstacle();
                } else {
                    cellule = new NS_Modele::CelluleMorte();
                }
                
                grille->definirCellule(x, y, cellule);
            }
        }
        
        return grille;
    }
    
    // Sauvegarde une grille dans un fichier texte
    // Format : hauteur largeur mode_torique(T/F) + matrice des états
    void Test::sauvegarderGrilleDansFichier(const std::string& nomFichier, const std::vector<std::vector<int>>& etat, bool torique) {
        std::ofstream fichier(nomFichier);
        if (!fichier.is_open()) return;
        
        int hauteur = etat.size();
        int largeur = etat[0].size();
        
        // En-tête du fichier
        fichier << hauteur << " " << largeur << " " << (torique ? "T" : "F") << std::endl;
        
        // Sauvegarde de la matrice
        for (int y = 0; y < hauteur; y++) {
            for (int x = 0; x < largeur; x++) {
                fichier << etat[y][x];
                if (x < largeur - 1) fichier << " ";
            }
            fichier << std::endl;
        }
        
        fichier.close();
    }
    
    bool Test::comparerGrilles(NS_Modele::Grille* grille1, NS_Modele::Grille* grille2) {
        if (!grille1 || !grille2) return false;
        return grille1->estIdentique(grille2);
    }
    
    void Test::afficherGrille(NS_Modele::Grille* grille, const std::string& titre) {
        if (!titre.empty()) {
            std::cout << titre << std::endl;
        }
        for (int y = 0; y < grille->getHauteur(); y++) {
            for (int x = 0; x < grille->getLargeur(); x++) {
                std::cout << grille->obtenirCellule(x, y)->getSymbole() << " ";
            }
            std::cout << std::endl;
        }
    }

    // Test 1 : Un bloc 2x2 doit rester stable (configuration vie immobile)
    bool Test::test1_BlocStable(TestRunner& runner) {
        std::vector<std::vector<int>> etat = {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        };
        
        NS_Modele::Grille* grille = creerGrille(4, 4, etat);
        NS_Modele::Grille* copie = grille->clone();
        NS_Modele::ReglesStandard* regle = new NS_Modele::ReglesStandard();
        
        grille->mettreAJour(regle);
        bool succes = comparerGrilles(grille, copie);
        
        delete grille;
        delete copie;
        delete regle;
        
        runner.afficherResultat("Test 1: Bloc stable", succes);
        return succes;
    }

    // Test 2 : Deux cellules isolées doivent mourir (moins de 2 voisins)
    bool Test::test2_Extinction(TestRunner& runner) {
        std::vector<std::vector<int>> etat = {
            {0, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 1},
            {0, 0, 0, 0}
        };
        
        NS_Modele::Grille* grille = creerGrille(4, 4, etat);
        NS_Modele::ReglesStandard* regle = new NS_Modele::ReglesStandard();
        
        grille->mettreAJour(regle);
        
        // Vérification que toutes les cellules sont mortes
        bool toutMort = true;
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                if (grille->obtenirCellule(x, y)->estVivante()) {
                    toutMort = false;
                }
            }
        }
        
        delete grille;
        delete regle;
        
        runner.afficherResultat("Test 2: Extinction", toutMort);
        return toutMort;
    }

    // Test 3 : Le planeur doit se déplacer correctement après 4 itérations
    bool Test::test3_Planeur(TestRunner& runner) {
        // Configuration initiale du planeur
        std::vector<std::vector<int>> etatInitial = {
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0},
            {0, 1, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0}
        };
        
        // Configuration attendue après 4 itérations (décalé d'une case en bas-droite)
        std::vector<std::vector<int>> etatAttendu = {
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0},
            {0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0}
        };
        
        NS_Modele::Grille* grille = creerGrille(7, 7, etatInitial);
        NS_Modele::Grille* reference = creerGrille(7, 7, etatAttendu);
        NS_Modele::ReglesStandard* regle = new NS_Modele::ReglesStandard();
        
        // Exécution de 4 itérations
        for (int i = 0; i < 4; i++) {
            grille->mettreAJour(regle);
        }
        
        bool succes = comparerGrilles(grille, reference);
        
        delete grille;
        delete reference;
        delete regle;
        
        runner.afficherResultat("Test 3: Planeur", succes);
        return succes;
    }

    // Test 4 : Le clignotant doit osciller entre deux états (période 2)
    bool Test::test4_Clignotant(TestRunner& runner) {
        // État 1 : vertical
        std::vector<std::vector<int>> etat1 = {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        };
        
        // État 2 : horizontal
        std::vector<std::vector<int>> etat2 = {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        };
        
        NS_Modele::Grille* grille = creerGrille(5, 5, etat1);
        NS_Modele::Grille* ref2 = creerGrille(5, 5, etat2);
        NS_Modele::Grille* ref1 = creerGrille(5, 5, etat1);
        NS_Modele::ReglesStandard* regle = new NS_Modele::ReglesStandard();
        
        // Première itération : doit passer à l'état 2
        grille->mettreAJour(regle);
        bool ok1 = comparerGrilles(grille, ref2);
        
        // Deuxième itération : doit revenir à l'état 1
        grille->mettreAJour(regle);
        bool ok2 = comparerGrilles(grille, ref1);
        
        bool succes = ok1 && ok2;
        
        delete grille;
        delete ref1;
        delete ref2;
        delete regle;
        
        runner.afficherResultat("Test 4: Clignotant", succes);
        return succes;
    }

    // Test 5 : Les obstacles ne doivent jamais changer d'état
    bool Test::test5_Obstacles(TestRunner& runner) {
        std::vector<std::vector<int>> etat = {
            {0, 0, 0, 0, 0},
            {0, 2, 1, 2, 0},
            {0, 1, 2, 1, 0},
            {0, 2, 1, 2, 0},
            {0, 0, 0, 0, 0}
        };
        
        NS_Modele::Grille* grille = creerGrille(5, 5, etat);
        NS_Modele::ReglesStandard* regle = new NS_Modele::ReglesStandard();
        
        // Comptage initial des obstacles
        int obstaclesAvant = 0;
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                if (grille->obtenirCellule(x, y)->estObstacle()) obstaclesAvant++;
            }
        }
        
        // Plusieurs itérations
        for (int i = 0; i < 5; i++) {
            grille->mettreAJour(regle);
        }
        
        // Comptage final des obstacles
        int obstaclesApres = 0;
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                if (grille->obtenirCellule(x, y)->estObstacle()) obstaclesApres++;
            }
        }
        
        bool succes = (obstaclesAvant == obstaclesApres && obstaclesAvant == 5);
        
        delete grille;
        delete regle;
        
        runner.afficherResultat("Test 5: Obstacles", succes);
        return succes;
    }

    // Test 6 : Le mode torique doit produire un résultat différent du mode normal
    // Configuration en bord de grille pour tester la connexion des bords
    bool Test::test6_ModeTorique(TestRunner& runner) {
        std::vector<std::vector<int>> etat = {
            {1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0},
            {1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        };
        
        // Grille avec mode torique activé
        NS_Modele::Grille* grilleTorique = creerGrille(5, 5, etat);
        grilleTorique->setModeTorique(true);
        
        // Grille avec mode normal
        NS_Modele::Grille* grilleNormale = creerGrille(5, 5, etat);
        grilleNormale->setModeTorique(false);
        
        NS_Modele::ReglesStandard* regle = new NS_Modele::ReglesStandard();
        
        grilleTorique->mettreAJour(regle);
        grilleNormale->mettreAJour(regle);
        
        // Comptage des cellules vivantes dans chaque grille
        int vivantesTorique = 0;
        int vivantesNormal = 0;
        
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                if (grilleTorique->obtenirCellule(x, y)->estVivante()) vivantesTorique++;
                if (grilleNormale->obtenirCellule(x, y)->estVivante()) vivantesNormal++;
            }
        }
        
        // Les résultats doivent être différents
        bool succes = (vivantesTorique != vivantesNormal);
        
        delete grilleTorique;
        delete grilleNormale;
        delete regle;
        
        runner.afficherResultat("Test 6: Mode torique", succes);
        return succes;
    }

    // Test 7 : Une grille vide doit rester vide
    bool Test::test7_GrilleVide(TestRunner& runner) {
        NS_Modele::Grille* grille = new NS_Modele::Grille(5, 5, false);
        NS_Modele::ReglesStandard* regle = new NS_Modele::ReglesStandard();
        
        grille->mettreAJour(regle);
        
        // Vérification que toutes les cellules sont mortes
        bool toutMort = true;
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                if (grille->obtenirCellule(x, y)->estVivante()) toutMort = false;
            }
        }
        
        delete grille;
        delete regle;
        
        runner.afficherResultat("Test 7: Grille vide", toutMort);
        return toutMort;
    }

    // Test 8 : Vérification des règles de Conway
    // Naissance avec 3 voisins, survie avec 2 ou 3, mort sinon
    bool Test::test8_ReglesConway(TestRunner& runner) {
        NS_Modele::ReglesStandard* regle = new NS_Modele::ReglesStandard();
        bool ok = true;
        
        // Test : naissance avec 3 voisins
        NS_Modele::CelluleMorte morte;
        NS_Modele::Cellule* res = regle->obtenirNouvelEtat(&morte, 3);
        if (!res->estVivante()) ok = false;
        delete res;
        
        // Test : survie avec 2 voisins
        NS_Modele::CelluleVivante vivante;
        res = regle->obtenirNouvelEtat(&vivante, 2);
        if (!res->estVivante()) ok = false;
        delete res;
        
        // Test : survie avec 3 voisins
        res = regle->obtenirNouvelEtat(&vivante, 3);
        if (!res->estVivante()) ok = false;
        delete res;
        
        // Test : mort par isolement (1 voisin)
        res = regle->obtenirNouvelEtat(&vivante, 1);
        if (res->estVivante()) ok = false;
        delete res;
        
        // Test : mort par surpopulation (4 voisins)
        res = regle->obtenirNouvelEtat(&vivante, 4);
        if (res->estVivante()) ok = false;
        delete res;
        
        delete regle;
        
        runner.afficherResultat("Test 8: Regles Conway", ok);
        return ok;
    }

    // Test 9 : Chargement d'une grille depuis un fichier
    // Vérifie la sauvegarde, le chargement et la simulation
    bool Test::test9_ChargementFichier(TestRunner& runner) {
        std::vector<std::vector<int>> etat = {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 0, 0}
        };
        
        std::string fichier = "test_planeur.txt";
        sauvegarderGrilleDansFichier(fichier, etat, false);
        
        // Chargement du fichier
        NS_Modele::Grille* grille = NS_Controleur::GestionFichier::chargerGrille(fichier);
        
        if (!grille) {
            runner.afficherResultat("Test 9: Chargement fichier", false);
            return false;
        }
        
        NS_Modele::ReglesStandard* regle = new NS_Modele::ReglesStandard();
        
        // Simulation de 3 itérations
        for (int i = 0; i < 3; i++) {
            grille->mettreAJour(regle);
        }
        
        // Comptage des cellules vivantes (le planeur doit toujours avoir 5 cellules)
        int vivantes = 0;
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                if (grille->obtenirCellule(x, y)->estVivante()) vivantes++;
            }
        }
        
        bool succes = (vivantes == 5);
        
        delete grille;
        delete regle;
        
        runner.afficherResultat("Test 9: Chargement fichier", succes);
        return succes;
    }

    // Test 10 : Détection de stabilisation
    // Une configuration stable doit être identique après mise à jour
    bool Test::test10_DetectionStabilisation(TestRunner& runner) {
        std::vector<std::vector<int>> etat = {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        };
        
        NS_Modele::Grille* grille = creerGrille(4, 4, etat);
        NS_Modele::ReglesStandard* regle = new NS_Modele::ReglesStandard();
        
        // Sauvegarde de l'état avant mise à jour
        NS_Modele::Grille* precedente = grille->clone();
        grille->mettreAJour(regle);
        
        // Vérification de l'identité
        bool stable = grille->estIdentique(precedente);
        
        delete grille;
        delete precedente;
        delete regle;
        
        runner.afficherResultat("Test 10: Stabilisation", stable);
        return stable;
    }

    // Exécute tous les tests unitaires et affiche le bilan final
    bool Test::executerTousLesTests() {
        std::cout << "\n========================================" << std::endl;
        std::cout << " TESTS UNITAIRES - JEU DE LA VIE" << std::endl;
        std::cout << "========================================\n" << std::endl;
        
        TestRunner runner;
        
        // Exécution de tous les tests
        test1_BlocStable(runner);
        test2_Extinction(runner);
        test3_Planeur(runner);
        test4_Clignotant(runner);
        test5_Obstacles(runner);
        test6_ModeTorique(runner);
        test7_GrilleVide(runner);
        test8_ReglesConway(runner);
        test9_ChargementFichier(runner);
        test10_DetectionStabilisation(runner);
        
        runner.afficherBilan();
        
        return runner.tousReussis();
    }

}