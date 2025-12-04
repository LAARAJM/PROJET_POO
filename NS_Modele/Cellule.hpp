#pragma once

namespace NS_Modele {
    class Cellule {
    private:

    public:
    
        virtual bool estVivante() = 0;

        virtual char getSymbole() = 0;

        virtual bool estObstacle() = 0;

        virtual Cellule* clone() = 0;

        virtual ~Cellule() = default;
    };

};

