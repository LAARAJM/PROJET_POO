#pragma once

namespace NS_Modele { //Namespace du modèle
    
    struct Position { //Structure représentant une position
        int x; //Coordonnée horizontale
        int y; //Coordonnée verticale
        
        bool estValide(int largeurMax, int hauteurMax); //Vérifie si la position est dans les limites
        
    };
}