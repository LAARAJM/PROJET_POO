#pragma once

#include <vector>
#include <string>

namespace NS_Modele { //Namespace du modèle
    class Grille; //Déclaration de la classe Grille
    class Regle; //Déclaration de la classe Règle
}

namespace NS_Vue { //Namespace du contrôleur
    class Affichage; //Déclaration de la classe Affichage
}

namespace NS_Controleur { //Namespace du contrôleur

    class Jeu { //Déclaration de la clase Jeu
    private:
        NS_Modele::Grille* grille; //Pointeur vers la grill actuelle
        NS_Modele::Regle* regle; //Pointeur vers la règle d'évolution
        NS_Vue::Affichage* affichage; //Pointeur vers l'affichage choisi
        int iterationCourante; //Compteur d'itérations 
        int iterationsMax; //Nombre maximal d'itérations 
        std::vector<NS_Modele::Grille*> grillesPrecedentes; //Historique des grilles pour vérifier la stabilité 

        void sauvegarderIterationCourante(); //Sauvegarde la grille de l'itaration

    public:
        Jeu(NS_Modele::Grille* g, NS_Modele::Regle* r, NS_Vue::Affichage* a, int nbIterations); //Constructeur du jeu
        
        ~Jeu(); //Destructeur du jeu

        void executer(); //Lance la boucle d'éxecution du jeu 

        void initialiser(); // Initalise l'affichage du jeu

        void etape(); //Effectue une itération du jeu

        bool doitArreter(); //Détermine si le jeu doit s'arrêter

        bool estStable(); //Vérifie si la grille ne change plus

        int getIteration() const; //Retourne l'itération courante

    };

}