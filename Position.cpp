#include "Position.hpp"

namespace NS_Modele {

    bool Position::estValide(int largeurMax, int hauteurMax) {
        return x >= 0 && x < largeurMax && y >= 0 && y < hauteurMax;
    }
}