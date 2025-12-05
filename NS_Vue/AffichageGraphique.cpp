#include "AffichageGraphique.hpp"
#include "Grille.hpp"
#include "Cellule.hpp"
#include <thread>
#include <chrono>
#include <iostream>

namespace NS_Vue { //Namespace de la vue 

    AffichageGraphique::AffichageGraphique(int taille, float delaiAffichage) 
        : fenetre(nullptr), // Fenêtre SFML initialement nulle
          tailleCellule(taille), //Taille en pixels d'une cellule
          delai(delaiAffichage), //Délai entre deux rafraîchissement
          fenetreFermee(false) { //Indique si la fenêtre a été fermée
        initialiserCouleurs();//Initialise les couleurs utilisées
    }

    AffichageGraphique::~AffichageGraphique() { //Destructeur
        nettoyer(); //Ferme la fenêtre proprement 
    }

    void AffichageGraphique::initialiserCouleurs() { 
        couleurs["vivante"]  = sf::Color::Green; //Couleur des cellules vivantes
        couleurs["morte"]    = sf::Color(60, 60, 60); //Cellules mortes -> Gris foncé
        couleurs["obstacle"] = sf::Color::Red; //Couleur des cellules obstacles
        couleurs["fond"]     = sf::Color::Black; //FOnd de la fenêtre
    }

    void AffichageGraphique::initialiser() { 
        if (fenetre) { //Si une fenêtre existe déjà
            delete fenetre; //On la supprime
        }

        fenetre = new sf::RenderWindow( //Création d'une fenêtre temporaire
            sf::VideoMode(800, 800), 
            "Jeu de la Vie - Conway",
            sf::Style::Close | sf::Style::Titlebar
        );
        
        fenetre->setFramerateLimit(60); //Limite de la fréquence d'affichage
        fenetreFermee = false; //Considère la fenêtre comme ouverte

        std::cout << "[INFO] Fenêtre graphique initialisée" << std::endl; 
    }

    void AffichageGraphique::afficher(NS_Modele::Grille* grille, int iteration) { 
        if (!fenetre || !fenetre->isOpen()) { //Si la fenêtre n'existe plus
            fenetreFermee = true; //On marque la fermeture
            return; //On arrête l'affichage
        }

        if (iteration == 0) { //Lors de la première itération
            int largeurFenetre = grille->getLargeur() * tailleCellule; //Calcule la largeur de la fenêtre
            int hauteurFenetre = grille->getHauteur() * tailleCellule; //Calcule la hauteur de la fenêtre
            

            const int MAX_SIZE = 50000; //Taille max pour éviter un crash
            if (largeurFenetre > MAX_SIZE || hauteurFenetre > MAX_SIZE) { 
                float scale = std::min( //Réduction proportionnelle des cellules
                    static_cast<float>(MAX_SIZE) / largeurFenetre,
                    static_cast<float>(MAX_SIZE) / hauteurFenetre
                );
                tailleCellule = static_cast<int>(tailleCellule * scale); //Nouvelle taille cellule
                largeurFenetre = grille->getLargeur() * tailleCellule; //Recalcule fenêtre
                hauteurFenetre = grille->getHauteur() * tailleCellule;
                std::cout << "[INFO] Taille de fenêtre réduite, nouvelle taille de cellule: " 
                          << tailleCellule << "px" << std::endl;
            }
            

            delete fenetre; //Supprime l'ancienne fenêtre
            fenetre = new sf::RenderWindow( //Crée une fenêtre adaptée à la grille
                sf::VideoMode(largeurFenetre, hauteurFenetre), 
                "Jeu de la Vie - Conway",
                sf::Style::Close | sf::Style::Titlebar
            );
            fenetre->setFramerateLimit(60); //Limite des fps
            
            std::cout << "[INFO] Fenêtre adaptée: " << largeurFenetre << "x" << hauteurFenetre 
                      << " pixels pour grille " << grille->getLargeur() << "x" << grille->getHauteur() 
                      << " cellules (taille cellule: " << tailleCellule << "px)" << std::endl;
        }

        fenetre->clear(couleurs["fond"]); //Efface la fenêtre avec la couleur de fond

        for (int y = 0; y < grille->getHauteur(); ++y) { //Parcourt chaque ligne
            for (int x = 0; x < grille->getLargeur(); ++x) { //Parcourt chaque colone
                NS_Modele::Cellule* cellule = grille->obtenirCellule(x, y); //Récupère d'une cellule
                
                if (!cellule) { //Vérifie la validité  
                    std::cerr << "[ERREUR] Cellule nulle à (" << x << "," << y << ")" << std::endl;
                    continue;
                }

                sf::RectangleShape rect( //Représentation graphique d'une cellule
                    sf::Vector2f(tailleCellule - 1.0f, tailleCellule - 1.0f)
                );
                rect.setPosition( //Positionne le carré
                    x * tailleCellule, 
                    y * tailleCellule
                );

                if (cellule->estObstacle()) { //Couleur selon le type de cellule
                    rect.setFillColor(couleurs["obstacle"]);
                } else if (cellule->estVivante()) {
                    rect.setFillColor(couleurs["vivante"]);
                } else {
                    rect.setFillColor(couleurs["morte"]);
                }

                fenetre->draw(rect); //Dessine la cellule
            }
        }

        fenetre->setTitle("Jeu de la Vie - Iteration " + std::to_string(iteration)); //Maj du titre

        fenetre->display(); //Affiche la frame

        gererEvenements(); //Gestion des évènements fenêtrés 
        
        std::this_thread::sleep_for( //Pause selon le délai choisi
            std::chrono::milliseconds(static_cast<int>(delai * 1000))
        );
    }

    void AffichageGraphique::nettoyer() {
        if (fenetre) { //Si la fenêtre existe
            if (fenetre->isOpen()) { //Si elle est ouverte
                fenetre->close(); //On la ferme 
            }
            delete fenetre; //On libère la mémoire
            fenetre = nullptr; //Sécurisation
        }
        std::cout << "[INFO] Fenêtre graphique fermée" << std::endl;
    }

    void AffichageGraphique::afficherMessage(const std::string& message) {
        std::cout << "[SFML] " << message << std::endl; //Affiche un message dans la console
    }

    bool AffichageGraphique::gererEvenements() {
        if (!fenetre || !fenetre->isOpen()) { //Si la fenêtre n'existe plus
            fenetreFermee = true; //On la marque comme fermée
            return false;
        }

        sf::Event event; //Objet évènement SFML
        while (fenetre->pollEvent(event)) { //Parcourt tous les évènements 
            if (event.type == sf::Event::Closed) { //Si l'utilisation ferme la fenêtre 
                fenetre->close(); //On la ferme
                fenetreFermee = true; //On signale la fermeture
                std::cout << "[INFO] Fenêtre fermée par l'utilisateur" << std::endl;
                return false; //Arrêt de l'affichage 
            }
        }
        
        return true; //Aucune fermeture 
    }

    bool AffichageGraphique::estFermee() const { 
        return fenetreFermee || (fenetre && !fenetre->isOpen()); //Retourne vrai si la fenêtre est fermée 
    }

}