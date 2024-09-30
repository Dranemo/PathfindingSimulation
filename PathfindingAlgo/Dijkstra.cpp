#include "Dijkstra.h"

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->weight > b->weight;
    }
};

void Dijkstra(Grid grid, Node* start) 
{
    // Initialiser la matrice des distances avec "infini"
    bool isFinish = false;
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;

    // Point de départ
    int startX = start->positionInMatrice.x;
    int startY = start->positionInMatrice.y;
    Node* current = grid.grid[startX][startY];
    current->weight = 0;
    pq.push(current);

    WindowManager* windowManager = WindowManager::GetInstance();


    while (!pq.empty() & !isFinish) {
        Node* current = pq.top();
        pq.pop();

        // Obtenir les voisins
        std::vector<Node*> neighbors = current->GetNeighbors(grid.grid);
        for (Node* neighbor : neighbors) {
            if (neighbor->GetState() != Node::visited && neighbor->GetState() != Node::start) {
                int newCost = current->weight + neighbor->weight; 
                neighbor->weight = newCost;
                neighbor->parent = current; // Suivre le chemin
                if (neighbor->GetState() == Node::finish) {
                    reconstructPath(current);
                    isFinish = true;
                    break;
                }
                else {
                    neighbor->SetState(Node::visited);
                }
                pq.push(neighbor);
            }
        }

        // Update
        if (windowManager->window.isOpen())
        {
            windowManager->Update();

            for (int i = 0; i < WindowManager::windowSize.y / Node::sizeNode.y; i++) {
                for (int j = 0; j < WindowManager::windowSize.x / Node::sizeNode.x; j++) {
                    grid.grid[i][j]->Update();
                }
            }
        }
    }

}

void reconstructPath(Node* finishNode)
{
    Node* current = finishNode;
    std::vector<Node*> path;
    while (current != nullptr) {
        path.push_back(current);
        current = current->parent;
    }
    std::reverse(path.begin(), path.end()); // Inverser pour obtenir le chemin correct
    for (Node* node : path) {
        node->SetState(Node::path);
    }
    std::cout << "FIN" << std::endl;
}