#include "Dijkstra.h"

int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->weight > b->weight;
    }
};

void Dijkstra(Grid grid) 
{
    // Initialiser la matrice des distances avec "infini"
    int shortest_path = 0;
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;

    // Point de départ
    int startX = 1;
    int startY = 1;
    Node* current = grid.grid[startX][startY];
    current->weight = 0;
    pq.push(current);

    WindowManager* windowManager = WindowManager::GetInstance();


    while (!pq.empty()) {
        Node* current = pq.top();
        pq.pop();

        //// Arrêter si nous atteignons le nœud de fin
        //if (current->GetState() == Node::finish) {
        //    std::cout << "Fin atteint avec un coût de " << current->weight << std::endl;
        //    reconstructPath(current); 
        //    break;
        //}

        // Obtenir les voisins
        std::vector<Node*> neighbors = current->GetNeighbors(grid.grid);
        for (Node* neighbor : neighbors) {
            if (neighbor->GetState() != Node::visited && neighbor->GetState() != Node::start) {
                int newCost = current->weight + neighbor->weight; // Ou une autre logique de coût
                neighbor->weight = newCost;
                neighbor->parent = current; // Suivre le chemin
                if (neighbor->GetState() == Node::finish) {
                    reconstructPath(current);
                    break;
                }
                else {
                    neighbor->SetState(Node::visited);
                }
                pq.push(neighbor);
            }
        }

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