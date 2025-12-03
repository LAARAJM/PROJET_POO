#include "AffichageGraphique.hpp"
#include "Grille.hpp"
#include "Cellule.hpp"
#include <thread>
#include <chrono>
#include <iostream>

namespace NS_Vue {

    AffichageGraphique::AffichageGraphique(int taille, float delaiAffichage)
        : tailleCellule(taille), 
          delai(delaiAffichage), 
          fenetre(nullptr),
          fenetreFermee(false) {
        initialiserCouleurs();
    }

    AffichageGraphique::~AffichageGraphique() {
        nettoyer();
    }

    void AffichageGraphique::initialiserCouleurs() {
        couleurs["vivante"]  = sf::Color::Green;
        couleurs["morte"]    = sf::Color(60, 60, 60);
        couleurs["obstacle"] = sf::Color::Red;
        couleurs["fond"]     = sf::Color::Black;
    }

    void AffichageGraphique::initialiser() {
        if (fenetre) {
            delete fenetre;
        }

        fenetre = new sf::RenderWindow(
            sf::VideoMode(800, 800), 
            "Jeu de la Vie - Conway",
            sf::Style::Close | sf::Style::Titlebar
        );
        
        fenetre->setFramerateLimit(60);
        fenetreFermee = false;

        std::cout << "[INFO] Fenêtre graphique initialisée (800x800)" << std::endl;
    }

    void AffichageGraphique::afficher(NS_Modele::Grille* grille, int iteration) {
        if (!fenetre || !fenetre->isOpen()) {
            fenetreFermee = true;
            return;
        }


        fenetre->clear(couleurs["fond"]);

 
        for (int y = 0; y < grille->getHauteur(); ++y) {
            for (int x = 0; x < grille->getLargeur(); ++x) {
                NS_Modele::Cellule* cellule = grille->obtenirCellule(x, y);
                
                if (!cellule) continue;

                sf::RectangleShape rect(
                    sf::Vector2f(tailleCellule - 1, tailleCellule - 1)
                );
                rect.setPosition(
                    x * tailleCellule, 
                    y * tailleCellule
                );

                if (cellule->estObstacle()) {
                    rect.setFillColor(couleurs["obstacle"]);
                } else if (cellule->estVivante()) {
                    rect.setFillColor(couleurs["vivante"]);
                } else {
                    rect.setFillColor(couleurs["morte"]);
                }

                fenetre->draw(rect);
            }
        }


        fenetre->display();

        gererEvenements();


        std::this_thread::sleep_for(
            std::chrono::milliseconds(static_cast<int>(delai * 1000))
        );
    }

    void AffichageGraphique::nettoyer() {
        if (fenetre) {
            if (fenetre->isOpen()) {
                fenetre->close();
            }
            delete fenetre;
            fenetre = nullptr;
        }
        std::cout << "[INFO] Fenêtre graphique fermée" << std::endl;
    }

    void AffichageGraphique::afficherMessage(const std::string& message) {
        std::cout << "[SFML] " << message << std::endl;
    }

    bool AffichageGraphique::gererEvenements() {
        if (!fenetre || !fenetre->isOpen()) {
            fenetreFermee = true;
            return false;
        }

        sf::Event event;
        while (fenetre->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                fenetre->close();
                fenetreFermee = true;
                std::cout << "[INFO] Fenêtre fermée par l'utilisateur" << std::endl;
                return false;
            }
            
        }
        
        return true;
    }

    bool AffichageGraphique::estFermee() const {
        return fenetreFermee || (fenetre && !fenetre->isOpen());
    }

}