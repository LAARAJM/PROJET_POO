#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include "Affichage.hpp"
#include "Grille.hpp"

namespace NS_Vue {

class AffichageConsole : public Affichage {
private:
    std::string dossierSortie;
    int numeroIteration;

public:
    AffichageConsole(const std::string& dossier)
        : dossierSortie(dossier), numeroIteration(0) {}

    void initialiser() override {
        std::filesystem::create_directories(dossierSortie);
        numeroIteration = 0;
    }

    void afficher(NS_Modele::Grille* grille, int n) override {
        numeroIteration = n;

        std::cout << "Iteration : " << n << std::endl;

        for (int y = 0; y < grille->getHauteur(); ++y) {
            for (int x = 0; x < grille->getLargeur(); ++x) {
                std::cout << grille->obtenirCellule(x, y)->getSymbole();
            }
            std::cout << std::endl;
        }

        // Sauvegarde dans un fichier
        std::ofstream fichier(dossierSortie + "/iter_" + std::to_string(n) + ".txt");
        for (int y = 0; y < grille->getHauteur(); ++y) {
            for (int x = 0; x < grille->getLargeur(); ++x) {
                fichier << grille->obtenirCellule(x, y)->getSymbole();
            }
            fichier << "\n";
        }
    }

    void nettoyer() override {
        std::cout << "Nettoyage console..." << std::endl;
    }

    void afficherMessage(const char* message) override {
        std::cout << "[MESSAGE] " << message << std::endl;
    }
};

}
