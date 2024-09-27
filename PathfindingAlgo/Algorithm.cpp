#include "Algorithm.h"
#include <thread>
#include <chrono>
#include <iostream>

#include "Grid.h"
#include "Node.h"

Node* Algorithm::visitingNode = nullptr;
bool Algorithm::threadOn = false;
std::vector<Node*> Algorithm::serchingQueue;
std::vector<Node*> Algorithm::path;
std::vector<Node*> Algorithm::walls;


void Algorithm::DFS(Grid* grid) {
	threadOn = true;
	GetWalls(grid);
	
	visitingNode = grid->GetStartNode();
	grid->SetNeighbourNodes(visitingNode);

	// Calcul du path (affichage vert)
	while (visitingNode != grid->GetFinishNode()) {

		if (!visitingNode->GetChilds().empty()) {
			bool allVisited = true;

			for (Node* n : visitingNode->GetChilds()) {
				if (n->GetState() != Node::visited) {
					serchingQueue.push_back(n);
					allVisited = false;
				}
			}

			if (!allVisited) {
				Node* newNode = serchingQueue[serchingQueue.size() - 1];

				newNode->SetParent(visitingNode);
				grid->SetNeighbourNodes(newNode);

				visitingNode = newNode;
				if(visitingNode != grid->GetFinishNode() && visitingNode != grid->GetStartNode())
					visitingNode->SetState(Node::visited);

				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			else {
				visitingNode = visitingNode->GetParent();
				serchingQueue.pop_back();
			}


		}

	}

	// Retour au début et vector path
	while (visitingNode != grid->GetStartNode()) {
		path.push_back(visitingNode);
		visitingNode = visitingNode->GetParent();
	}

	// Affichage du path
	for (int i = path.size() - 1; i >= 0; i--) {
		path[i]->SetState(Node::path);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::cout << "DFS Finished \n";
	threadOn = false;
}




void Algorithm::BFS(Grid* grid) {
	GetWalls(grid);

	visitingNode = grid->GetStartNode();
	grid->SetNeighbourNodes(visitingNode);

	while (visitingNode != grid->GetFinishNode()) {


	}
}

void Algorithm::GetWalls(Grid* grid) {


	for (int i = 0; i < WindowManager::windowSize.y / Node::sizeNode.y; i++) {
		for (int j = 0; j < WindowManager::windowSize.x / Node::sizeNode.x; j++) {
			if (grid->grid[i][j]->GetState() == Node::wall) {
				walls.push_back(grid->grid[i][j]);
			}
		}
	}

}