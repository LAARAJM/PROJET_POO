#include "FabriqueDeJeu.hpp"
#include "Jeu.hpp"
#include "Test.hpp"
#include <iostream>
#include <string>
#include <algorithm>

void afficherAide() {
    std::cout << "========================================" << std::endl;
    std::cout << "   JEU DE LA VIE - AIDE                " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    std::cout << "USAGE:" << std::endl;
    std::cout << "  ./main [fichier] [mode] [iterations]" << std::endl;
    std::cout << "  ./main test                           " << std::endl;
    std::cout << std::endl;
    std::cout << "EXEMPLES:" << std::endl;
    std::cout << "  ./main grille.txt graphique 100      - Lance le jeu en mode graphique" << std::endl;
    std::cout << "  ./main grille.txt console 50         - Lance le jeu en mode console" << std::endl;
    std::cout << "  ./main test                          - Lance la suite de tests" << std::endl;
    std::cout << std::endl;
    std::cout << "PARAMETRES:" << std::endl;
    std::cout << "  fichier    : Fichier de grille initiale (défaut: grille.txt)" << std::endl;
    std::cout << "  mode       : 'console' ou 'graphique' (défaut: graphique)" << std::endl;
    std::cout << "  iterations : Nombre maximum d'itérations (défaut: 100)" << std::endl;
    std::cout << "========================================" << std::endl;
}

int main(int argc, char* argv[]) {

    if (argc > 1) {
        std::string arg = argv[1];
        std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
        
        if (arg == "help") {
            afficherAide();
            return 0;
        }
        
        // MODIFICATION: Appel de la méthode statique executerTousLesTests()
        if (arg.find("test") != std::string::npos) {
            std::cout << std::endl;
            std::cout << "Lancement de la suite de tests..." << std::endl;
            std::cout << std::endl;
            
            bool testsReussis = NS_Test::Test::executerTousLesTests();
            
            std::cout << std::endl;
            if (testsReussis) {
                std::cout << "Tous les tests ont réussi." << std::endl;
            } else {
                std::cout << "Certains tests ont échoué." << std::endl;
            }
            std::cout << std::endl;
            
            return testsReussis ? 0 : 1;
        }
    }
    
    std::string fichierGrille = "grille.txt";
    std::string mode = "graphique";
    int iterations = 100;

    if (argc > 1) {
        fichierGrille = argv[1];
    }
    if (argc > 2) {
        mode = argv[2];
    }
    if (argc > 3) {
        iterations = std::stoi(argv[3]);
    }

    std::cout << "==================================" << std::endl;
    std::cout << "   JEU DE LA VIE    " << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "Fichier: " << fichierGrille << std::endl;
    std::cout << "Mode: " << mode << std::endl;
    std::cout << "Iterations max: " << iterations << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << std::endl;

    NS_Controleur::Jeu* jeu = NS_Controleur::FabriqueDeJeu::creerDepuisFichier(
        fichierGrille, 
        mode, 
        iterations
    );

    if (!jeu) {
        std::cerr << "[ERREUR] Impossible de creer le jeu." << std::endl;
        return 1;
    }

    try {
        jeu->initialiser();
        jeu->executer();
    } catch (const std::exception& e) {
        std::cerr << "[ERREUR] Exception: " << e.what() << std::endl;
        delete jeu;
        return 1;
    }

    delete jeu;

    std::cout << std::endl;
    std::cout << "Simulation terminee." << std::endl;
    
    return 0;
}