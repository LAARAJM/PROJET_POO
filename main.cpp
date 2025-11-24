#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

// test pour github
const int tailleCellule = 20; // Taille d'une cellule en pixels
const int largeur = 50; // Nombre de cellules en largeur
const int longueur = 50; // Nombre de cellules en hauteur

std::vector<std::vector<int>> grid(largeur, std::vector<int>(longueur));

void initializeGrid() { // Initialise la grille avec des valeurs aléatoires
    std::srand(std::time(0)); 
    for (int x = 0; x < largeur; ++x) {
        for (int y = 0; y < longueur; ++y) {
            grid[x][y] = std::rand() % 2;  // affiche aléatoirement 0 ou 1
        }
    }
}

void renderGrid(sf::RenderWindow &window) { // Affiche la grille
    int x, y;
    
    window.clear(); // Efface la fenêtre
    sf::RectangleShape cell(sf::Vector2f(tailleCellule - 1.0f, tailleCellule - 1.0f)); // Crée une cellule
    for (x = 0; x < largeur; ++x) {
        for (y = 0; y < longueur; ++y) {
            if (grid[x][y] == 1) { // Si la cellule est vivante
                cell.setPosition(x * tailleCellule, y * tailleCellule); // Positionne la cellule
                window.draw(cell); // Dessine la cellule
            }
        }
    }
    window.display(); // Affiche tout ce qui a été dessiné
}

int main() {
    sf::RenderWindow window(sf::VideoMode(largeur * tailleCellule, longueur * tailleCellule), "Game of Life"); // Crée une fenêtre SFML
 

    while (window.isOpen()) { // Boucle principale
        sf::Event event; 
        while (window.pollEvent(event)) { 
            if (event.type == sf::Event::Closed)  // Si le bouton de fermeture est cliqué
                window.close(); // Ferme la fenêtre
        }
        initializeGrid();
        renderGrid(window); // Affiche la grille actuelle
        
        sf::sleep(sf::milliseconds(100)); //controle la vitesse d'affichage
    }

    return 0;
}
