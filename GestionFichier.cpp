#include "JdV/Utils/GestionFichier.hpp"
#include "JdV/Modele/Grille.hpp" 
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace JdV {
namespace Utils {


DonneesGrille GestionFichier::lireFichier(const std::string& cheminFichier) {
    std::ifstream fichier(cheminFichier);
    if (!fichier.is_open()) {
        throw std::runtime_error("Erreur: Impossible d'ouvrir le fichier d'entrée : " + cheminFichier);
    }

    DonneesGrille donnees;
    std::string ligne;


    if (!std::getline(fichier, ligne)) {
        throw std::runtime_error("Erreur: Le fichier est vide ou corrompu.");
    }
    std::stringstream ss(ligne);
    if (!(ss >> donnees.hauteur >> donnees.largeur)) {
        throw std::runtime_error("Erreur: Format de dimensions incorrect dans la première ligne.");
    }

    if (donnees.hauteur <= 0 || donnees.largeur <= 0) {
        throw std::runtime_error("Erreur: Dimensions de grille non valides.");
    }

    donnees.cellules.resize(donnees.hauteur, std::vector<int>(donnees.largeur));
    
    for (int i = 0; i < donnees.hauteur; ++i) {
        if (!std::getline(fichier, ligne)) {
            throw std::runtime_error("Erreur: Le fichier ne contient pas assez de lignes pour la hauteur spécifiée.");
        }
        
        std::stringstream ligne_ss(ligne);
        for (int j = 0; j < donnees.largeur; ++j) {
            int etat;
            if (!(ligne_ss >> etat)) {
                std::stringstream err;
                err << "Erreur: La ligne " << i + 2 << " est trop courte ou contient un format invalide.";
                throw std::runtime_error(err.str());
            }
            donnees.cellules[i][j] = etat; 
        }
    }

    return donnees;
}

void GestionFichier::ecrireFichier(const std::string& cheminBase, 
                                  const JdV::Modele::Grille& grille,
                                  int iteration) {
    
    std::filesystem::path base(cheminBase);
    std::string dossierSortie = base.stem().string() + "_out";

    try {
        if (!std::filesystem::exists(dossierSortie)) {
            std::filesystem::create_directory(dossierSortie);
        }
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors de la création du dossier de sortie : " << dossierSortie << " : " << e.what() << std::endl;
        return;
    }

    std::string cheminFichier = dossierSortie + "/etat_" + std::to_string(iteration) + ".txt";
    std::ofstream fichier(cheminFichier);

    if (!fichier.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier en écriture : " << cheminFichier << std::endl;
        return;
    }


    fichier << grille.getHauteur() << " " << grille.getLargeur() << "\n";

    for (int i = 0; i < grille.getHauteur(); ++i) {
        for (int j = 0; j < grille.getLargeur(); ++j) {
            fichier << (grille.getCellule(i, j).estVivante() ? 1 : 0);
            if (j < grille.getLargeur() - 1) {
                fichier << " ";
            }
        }
        fichier << "\n";
    }

    fichier.close();
}

}
}