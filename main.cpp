#include "FabriqueDeJeu.hpp"
#include "Jeu.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    
    // Paramètres par défaut
    std::string fichierGrille = "grille.txt";
    std::string mode = "graphique";
    int iterations = 100;

    // Parser les arguments de ligne de commande
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
    std::cout << "   JEU DE LA VIE - Conway" << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << "Fichier: " << fichierGrille << std::endl;
    std::cout << "Mode: " << mode << std::endl;
    std::cout << "Iterations max: " << iterations << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << std::endl;

    // Créer le jeu à partir du fichier
    NS_Controleur::Jeu* jeu = NS_Controleur::FabriqueDeJeu::creerDepuisFichier(
        fichierGrille, 
        mode, 
        iterations
    );

    if (!jeu) {
        std::cerr << "[ERREUR] Impossible de creer le jeu." << std::endl;
        std::cerr << "Verifiez que le fichier existe et est au bon format." << std::endl;
        std::cerr << std::endl;
        std::cerr << "Usage: ./main [fichier] [mode] [iterations]" << std::endl;
        std::cerr << "  fichier: chemin vers le fichier de grille (defaut: grille.txt)" << std::endl;
        std::cerr << "  mode: 'console' ou 'graphique' (defaut: graphique)" << std::endl;
        std::cerr << "  iterations: nombre max d'iterations (defaut: 100)" << std::endl;
        return 1;
    }

    // Initialiser et exécuter le jeu
    try {
        jeu->initialiser();
        jeu->executer();
    } catch (const std::exception& e) {
        std::cerr << "[ERREUR] Exception: " << e.what() << std::endl;
        delete jeu;
        return 1;
    }

    // Nettoyer
    delete jeu;

    std::cout << std::endl;
    std::cout << "Simulation terminee." << std::endl;
    
    return 0;
}