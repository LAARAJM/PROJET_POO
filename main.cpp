#include "NS_Controleur/FabriqueDeJeu.hpp"
#include "NS_Controleur/Jeu.hpp"
#include "TEST/Test.hpp"
#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string arg = argv[1];
        std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower);
        
        if (arg.find("test") != std::string::npos) {
            std::cout << std::endl;
            std::cout << "Lancement de la suite de tests..." << std::endl;
            std::cout << std::endl;
            
            bool testsReussis = NS_Test::Test::executerTousLesTests();
            
            std::cout << std::endl;
            if (testsReussis) {
                std::cout << "✓ Tous les tests ont réussi." << std::endl;
            } else {
                std::cout << "✗ Certains tests ont échoué." << std::endl;
            }
            std::cout << std::endl;
            return testsReussis ? 0 : 1;
        }
    }
    
    // Paramètres par défaut
    std::string fichierGrille = "grille.txt";
    std::string mode = "graphique";
    int iterations = 100;

    // Lecture des arguments
    if (argc > 1) {
        fichierGrille = argv[1];
    }
    if (argc > 2) {
        mode = argv[2];
    }
    if (argc > 3) {
        try {
            iterations = std::stoi(argv[3]);
            if (iterations <= 0) {
                std::cerr << "[ERREUR] Le nombre d'iterations doit etre positif." << std::endl;
                return 1;
            }
        } catch (const std::exception& e) {
            std::cerr << "[ERREUR] Nombre d'iterations invalide: " << argv[3] << std::endl;
            return 1;
        }
    }

    // Validation du mode
    if (mode != "console" && mode != "graphique") {
        std::cerr << "[ERREUR] Mode invalide. Utilisez 'console' ou 'graphique'." << std::endl;
        return 1;
    }

    // Affichage des informations de lancement
    std::cout << "==================================" << std::endl;
    std::cout << "   JEU DE LA VIE - CONWAY        " << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "Fichier      : " << fichierGrille << std::endl;
    std::cout << "Mode         : " << mode << std::endl;
    std::cout << "Iterations   : " << iterations << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << std::endl;

    // Création du jeu
    NS_Controleur::Jeu* jeu = NS_Controleur::FabriqueDeJeu::creerDepuisFichier(
        fichierGrille, 
        mode, 
        iterations
    );

    if (!jeu) {
        std::cerr << "[ERREUR] Impossible de creer le jeu." << std::endl;
        std::cerr << "Verifiez que le fichier existe et respecte le bon format." << std::endl;
        std::cerr << "Consultez le README.md pour plus d'informations." << std::endl;
        return 1;
    }


    try {
        jeu->initialiser();
        jeu->executer();
    } catch (const std::exception& e) {
        std::cerr << "[ERREUR] Exception durant l'execution: " << e.what() << std::endl;
        delete jeu;
        return 1;
    }

    delete jeu;

    std::cout << std::endl;
    std::cout << "Simulation terminee avec succes." << std::endl;
    std::cout << "Les resultats sont sauvegardes dans le dossier 'jeu_de_la_vie/'." << std::endl;
    std::cout << std::endl;
    
    return 0;
}