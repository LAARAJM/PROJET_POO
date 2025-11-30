#pragma once

#include "JdV/Vue/Affichage.hpp"
#include <string>

namespace JdV {
namespace Vue {

/**
 * @brief Implémentation de l'affichage en mode console.
 * Gère l'affichage sur la sortie standard et l'écriture des états dans les fichiers.
 */
class AffichageConsole : public Affichage {
private:
    // Chemin de base du fichier d'entrée, utilisé pour créer le dossier de sortie (_out)
    std::string cheminBaseFichier; 
public:
    /**
     * @brief Constructeur.
     * @param cheminBase Le chemin du fichier d'entrée initial.
     */
    AffichageConsole(const std::string& cheminBase);
    
    // Implémentation de l'interface Affichage
    void initialiser() override;
    void nettoyer() override;

    /**
     * @brief Affiche l'état de la grille sur la console et écrit le fichier de sortie.
     */
    void afficher(const JdV::Modele::Grille& grille, int iteration) override;
    
    // En mode console, le processus continue tant que le moteur le permet.
    bool estOuvert() const override { return true; } 
    void gererEntree() override {} // Rien à faire en console
};

} 
}