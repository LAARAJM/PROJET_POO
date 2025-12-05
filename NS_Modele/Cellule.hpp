#pragma once

namespace NS_Modele { //Namespace du modèle
    class Cellule { //Déclaration de la classe Cellule
    private:

    public:
    
        virtual bool estVivante() = 0; //Indique si la cellule est vivante

        virtual char getSymbole() = 0; //Retourne le symbole représentant la cellule

        virtual bool estObstacle() = 0; //Indique si la cellule est un obstacle

        virtual Cellule* clone() = 0; //Crée une copie polymorphique de la cellule

        virtual ~Cellule() = default; //Destructeur virtuel par défaut
    };

};

