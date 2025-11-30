#pragma once

#include <memory> // Pour std::unique_ptr

namespace JdV {
namespace Modele {

/**
 * @brief Classe Abstraite Cellule.
 * Implémente le Pattern Prototype via clone().
 */
class Cellule {
public:
    virtual ~Cellule() = default;
    virtual bool estVivante() const = 0;
    virtual char getSymbole() const = 0; 
    virtual bool estObstacle() const { return false; } 
    virtual std::unique_ptr<Cellule> clone() const = 0;
};

// Déclarations anticipées des classes concrètes
class CelluleVivante;
class CelluleMorte;


} // namespace Modele
}