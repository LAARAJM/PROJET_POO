#include "NS_Controleur/FabriqueDeJeu.hpp"
#include "NS_Controleur/Jeu.hpp"
#include "TEST/Test.hpp"
#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char* argv[]) { //Point d'entrée du programme
    if (argc > 1) { //Si un argument est passé 
        std::string arg = argv[1]; //Récupère le premier argument 
        std::transform(arg.begin(), arg.end(), arg.begin(), ::tolower); //Convertit en minuscules
        
        if (arg.find("test") != std::string::npos) { //Si on demande à lancer le test
            std::cout << std::endl;
            std::cout << "Lancement de la suite de tests..." << std::endl;
            std::cout << std::endl;
            
            bool testsReussis = NS_Test::Test::executerTousLesTests(); //Lance tous les tests
            
            std::cout << std::endl;
            if (testsReussis) { //Si réussite
                std::cout << " Tous les tests ont réussi." << std::endl;
            } else { //Sinon
                std::cout << " Certains tests ont échoué." << std::endl;
            }
            std::cout << std::endl;
            return testsReussis ? 0 : 1; //Retourne 0 si OK, 1 si erreur
        }
    }
    
    // Paramètres par défaut
    std::string fichierGrille = "Grilles/grille.txt"; //Fichier de la grille par défaut
    std::string mode = "graphique"; //Mode d'affichage par défaut
    int iterations = 100; //Nombre d'itérations par défaut

    // Lecture des arguments
    if (argc > 1) { 
        fichierGrille = argv[1]; //Premier argument -> fichier
    }
    if (argc > 2) {
        mode = argv[2]; //Deuxième argument -> mode
    }
    if (argc > 3) { //Troisième argument -> nombre d'itérations
        try {
            iterations = std::stoi(argv[3]); //Convertit en entier
            if (iterations <= 0) { //Vérifie si positif
                std::cerr << "[ERREUR] Le nombre d'iterations doit etre positif." << std::endl;
                return 1;
            }
        } catch (const std::exception& e) { //Si conversion invalide
            std::cerr << "[ERREUR] Nombre d'iterations invalide: " << argv[3] << std::endl;
            return 1;
        }
    }

    // Validation du mode
    if (mode != "console" && mode != "graphique") { //Mode inconnue ?
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
        fichierGrille, //Fichier à charger
        mode, //Mode d'affichage 
        iterations //Nombre d'itérations
    );

    if (!jeu) { //Vérifie si la fabrique a échoué
        std::cerr << "[ERREUR] Impossible de creer le jeu." << std::endl;
        std::cerr << "Verifiez que le fichier existe et respecte le bon format." << std::endl;
        std::cerr << "Consultez le README.md pour plus d'informations." << std::endl;
        return 1;
    }


    try {
        jeu->initialiser(); //Initialise l'affichage 
        jeu->executer(); //Lance la simulation
    } catch (const std::exception& e) { //Gestion d'erreur en cas d'exception
        std::cerr << "[ERREUR] Exception durant l'execution: " << e.what() << std::endl;
        delete jeu;
        return 1;
    }

    delete jeu; //Libère la mémoire

    std::cout << std::endl;
    std::cout << "Simulation terminee avec succes." << std::endl;
    std::cout << "Les resultats sont sauvegardes dans le dossier 'jeu_de_la_vie/'." << std::endl;
    std::cout << std::endl;
    
    return 0; //Quitte le programme correctement
}