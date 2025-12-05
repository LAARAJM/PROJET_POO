#pragma once

#include <string>

namespace NS_Modele { //Namespace du modèle
    class Grille; //Déclaration anticipée de la classe Grille
}

namespace NS_Controleur { //Namesapce du contrôleur

    class GestionFichier { //Déclaration de la classe GestionFichier
    public:
        //Méthode statique pour charger une grille 
        static NS_Modele::Grille* chargerGrille(const std::string& cheminFichier); //Paramètre : chemin du fichier à lire
        
        //Méthode statique pour sauvegarder une grille
        static void sauvegarderGrille(const std::string& cheminFichier, //Paramètre : dossier ou fichier de sortie
                                      NS_Modele::Grille* grille, //Paramètre : grille à sauvegarder
                                      int iteration); //Paramètre : numéro de l'itération
        
        //Méthode statique pour valider un fichier
        static bool validerFormat(const std::string& cheminFichier); //Paramètre : chemin du fichier à vérifier
    };

}