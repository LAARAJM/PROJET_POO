#pragma once

namespace NS_Modele {
    
    struct Position {
        int x;
        int y;
        
        bool estValide(int largeurMax, int hauteurMax);
        
    };
}