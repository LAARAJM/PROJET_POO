#pragma once

#include <memory>
#include <vector>


namespace JdV { namespace Modele { class Grille; } }

namespace JdV {
namespace Controlleur {

class Iterations {
private:
    int iterationCourante = 0;
    const int iterationsMax = 20;
    

    std::vector<std::unique_ptr<JdV::Modele::Grille>> historique;
    const int tailleHistorique = 5; 

public:
    Iterations() = default;

    void iterationSuivante();
    
    int getIterationCourante() const { return iterationCourante; }
    
   
    bool doitArreter() const;
    

    void sauvegarderEtat(const JdV::Modele::Grille& grille);
    

    bool estStable(const JdV::Modele::Grille& grille) const;
};

} 
}