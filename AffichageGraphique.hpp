#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>

#include "Affichage.hpp"
#include "Grille.hpp"

namespace NS_Vue {

class AffichageGraphique : public Affichage {
private:
    sf::RenderWindow* fenetre;
    int tailleCellule;
    float delai;
    std::map<std::string, sf::Color> couleurs;
    bool fenetreFermee;

public:

    AffichageGraphique(int taille = 20, float delaiAffichage = 0.1f)
        : tailleCellule(taille), delai(delaiAffichage), fenetre(nullptr),
          fenetreFermee(false) 
    {
        couleurs["vivante"] = sf::Color::Green;
        couleurs["morte"]   = sf::Color(60,60,60);
        couleurs["obstacle"]= sf::Color::Red;
    }

    void initialiser() override {
        fenetre = new sf::RenderWindow(sf::VideoMode(800, 800), "Jeu de la Vie - SFML");
        fenetreFermee = false;
    }

    void afficher(NS_Modele::Grille* grille, int iteration) override {
        if (!fenetre || !fenetre->isOpen()) return;

        fenetre->clear(sf::Color::Black);

        for (int y = 0; y < grille->getHauteur(); ++y) {
            for (int x = 0; x < grille->getLargeur(); ++x) {

                auto c = grille->obtenirCellule(x, y);

                sf::RectangleShape rect(sf::Vector2f(tailleCellule, tailleCellule));
                rect.setPosition(x * tailleCellule, y * tailleCellule);

                if (c->estObstacle())
                    rect.setFillColor(couleurs["obstacle"]);
                else if (c->estVivante())
                    rect.setFillColor(couleurs["vivante"]);
                else
                    rect.setFillColor(couleurs["morte"]);

                fenetre->draw(rect);
            }
        }

        fenetre->display();

        std::this_thread::sleep_for(std::chrono::milliseconds((int)(delai * 1000)));

        gererEvenements();
    }

    void nettoyer() override {
        if (fenetre) {
            fenetre->close();
            delete fenetre;
            fenetre = nullptr;
        }
    }

    void afficherMessage(const char* message) override {
        std::cout << "[SFML] " << message << std::endl;
    }

    bool gererEvenements() {
        if (!fenetre) return false;

        sf::Event event;
        while (fenetre->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                fenetre->close();
                fenetreFermee = true;
                return false;
            }
        }
        return true;
    }

    bool estFermee() const {
        return fenetreFermee;
    }
};

}
