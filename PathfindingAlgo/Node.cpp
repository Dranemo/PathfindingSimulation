#include "Node.h"
sf::Vector2f Node::sizeNode = sf::Vector2f(30, 30);


std::vector<Node*> Node::GetNeighbors(const std::vector<std::vector<Node*>>& grid) {
    std::vector<Node*> neighbors;

    // Vérifier les voisins dans les 4 directions principales
    if (positionInMatrice.x > 0)
        neighbors.push_back(grid[positionInMatrice.x - 1][positionInMatrice.y]); // Haut

    if (positionInMatrice.x < grid.size() - 1)
        neighbors.push_back(grid[positionInMatrice.x + 1][positionInMatrice.y]); // Bas

    if (positionInMatrice.y > 0)
        neighbors.push_back(grid[positionInMatrice.x][positionInMatrice.y - 1]); // Gauche

    if (positionInMatrice.y < grid[0].size() - 1)
        neighbors.push_back(grid[positionInMatrice.x][positionInMatrice.y + 1]); // Droite

    return neighbors;
}
