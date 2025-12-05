#pragma once

#include <string>
#include "Jeu.hpp"
#include "GestionFichier.hpp"

namespace NS_Controleur { //Début du namespace Controleur

    class FabriqueDeJeu { //Déclaration de la classe FabriqueDeJeu
    public:
        //Méthode statique créant un Jeu
        static NS_Controleur::Jeu* creerDepuisFichier(const std::string& fichier, //Paramètre : chemin du fichier à changer
                                        const std::string& mode, //Paramètre : mode d'affichage ("console" ou "graphique")
                                        int iterMax = -1); //Paramètre : nombre max d'itérations (-1 pour illimité)
    };

} //Fin du namespace Controleur

 