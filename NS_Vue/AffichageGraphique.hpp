#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Affichage.hpp"


namespace NS_Modele {
    class Grille;
}

namespace NS_Vue {

    class AffichageGraphique : public Affichage {
    private:
        sf::RenderWindow* fenetre;
        int tailleCellule;
        float delai;
        std::map<std::string, sf::Color> couleurs;
        bool fenetreFermee;

        void initialiserCouleurs();

    public:
        AffichageGraphique(int taille = 900, float delaiAffichage = 0.3f);

        ~AffichageGraphique();

        void initialiser() override;

        void afficher(NS_Modele::Grille* grille, int iteration) override;

        void nettoyer() override;

        void afficherMessage(const std::string& message) override;

        bool gererEvenements();

        bool estFermee() const;
    };

}