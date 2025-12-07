#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Affichage.hpp"


namespace NS_Modele { //Namespace du modèle
    class Grille; //Déclaration de la classe Grille
}

namespace NS_Vue { //Namespace de la vue 

    class AffichageGraphique : public Affichage { //La classe Affichage Graphique hérite de la classe abstraite Affichage
    private:
        sf::RenderWindow* fenetre; //Fenêtre SFML utilisée pour l'affichage
        int tailleCellule; //Taille en pixels de chaque cellule
        float delai; //Délai entre deux affichages 
        std::map<std::string, sf::Color> couleurs; //Map stockant les couleurs selon le type de cellule
        bool fenetreFermee; //Indique si le fenêtre a été fermée
        bool enPause; //Indique si la simulation est en pause

        void initialiserCouleurs(); //Initialise les couleurs à utiliser

    public:
        AffichageGraphique(int taille = 900, float delaiAffichage = 0.3f); //Constructeur avec valeurs par défaut

        ~AffichageGraphique(); //Destructeur 

        void initialiser() override; //Initialise la fenêtre graphique

        void afficher(NS_Modele::Grille* grille, int iteration) override; //Affiche une grille à une itération donnée

        void nettoyer() override; //Ferme et nettoie la fenêtre

        void afficherMessage(const std::string& message) override; //Affiche un message dans la console

        bool gererEvenements(); //Gère les évènements SFML 

        bool estFermee() const; //Vérifie si la fenêtre est fermée

        bool estEnPause() const; //Vérifie si la simulation est en pause
    };

}