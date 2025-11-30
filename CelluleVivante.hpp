#pragma once

#include "Cellule.hpp"

namespace JdV {
namespace Modele {

class CelluleVivante : public Cellule {
public:
    bool estVivante() const override { return true; }
    char getSymbole() const override { return '1'; }
    std::unique_ptr<Cellule> clone() const override {
        return std::make_unique<CelluleVivante>();
    }
};

}
}